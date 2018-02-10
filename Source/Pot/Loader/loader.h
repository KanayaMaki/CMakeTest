//
//	content	:	別スレッドでロードしてくれるクラス
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Thread/thread.h"
#include "./Pot/Thread/mutex.h"
#include "./Pot/Out/out.h"
#include "./Pot/List/vector.h"
#include "./Pot/Sleep/sleep.h"

#include "./Pot/Usefull/singleton.h"


namespace cpot {


class Loader {
public:
	//ローダスレッドで実行される、ロード処理
	virtual void Load() = 0;
	
	//メインスレッドで実行される、ロード開始前の処理
	//!Startの中からLoaderをRegistしてはいけない
	virtual void Start() {}
	
	//メインスレッドで実行される、ロード終了後の処理
	virtual void Finish() {}

	//優先すべきか
	virtual BOOL IsHurry() const {
		return false;
	}
};


class LoaderManager : public Singleton<LoaderManager> {
	friend class Singleton<LoaderManager>;

private:
	LoaderManager() {
		mNowLoadingCount = 0;
	}
	~LoaderManager() {
		Clear();
	}

	//ロードを開始する
	#pragma region Start

public:
	//ローダスレッドを起動する
	void Start(u32 aThreadNum) {
		#ifndef CPOT_ON_ANDROID
		//指定された引数分のスレッドを起動する
		for (u32 i = 0; i < aThreadNum; i++) {
			SetEnd(i, false);
			mThread[i].Start(Load, (u32*)i);
		}
		#endif
	}

	//ローダスレッドの数を、指定された数にする
	void Resize(u32 aThreadNum) {
		for (u32 i = 0; i < cThreadMaxNum; i++) {
			//起動予定のスレッドなら
			if (i < aThreadNum) {
				SetEnd(i, false);
				mThread[i].Start(Load, (u32*)i);
			}
			//停止予定のスレッドなら
			if (i >= aThreadNum) {
				SetEnd(i, true);
			}
		}
	}

	#pragma endregion


	//ロードを停止する
	#pragma region Stop

public:
	//ローダスレッドを終了する
	void Stop() {

		//全スレッドの終了
		for (u32 i = 0; i < cThreadMaxNum; i++) {
			SetEnd(i, true);
		}
	}

	//ローダスレッドを終了して、待つ
	void Join() {

		//全スレッドの終了
		Stop();

		//全スレッドの合流を待つ
		for (u32 i = 0; i < cThreadMaxNum; i++) {
			mThread[i].Join();
		}
	}

	#pragma endregion


	//現在登録されているローダを全てクリアする
	#pragma region Clear

	void Clear() {
		Join();
		Delete(mLoaderListNormal);
		Delete(mLoaderListHurry);
		Delete(mLoaderListFinish);
		mNowLoadingCount = 0;
	}

	#pragma endregion


	//別スレッドで実行されて、読み込む
	#pragma region Load

private:
	Loader* GetLoader() {

		Loader* l = nullptr;

		MutexLocker m0(mLoaderListNormalMutex);
		MutexLocker m1(mLoaderListHurryMutex);

		//もし急ぎのローダが存在するなら
		if (mLoaderListHurry.GetSize() != 0) {
			//一番後ろのローダを取得する
			l = mLoaderListHurry.PopBack();
		}
		//もし通常のローダが存在するなら
		else if (mLoaderListNormal.GetSize() != 0) {
			//一番後ろのローダを取得する
			l = mLoaderListNormal.PopBack();
		}

		if (l) {
			LoadStart();	//ロード開始
		}

		return l;
	}
	static void* Load(u32* aThreadIndex) {

		Sleep lSleep;

		u32 lThreadIndex = (Pointer)aThreadIndex;

		while (true) {

			Loader* l = S().GetLoader();

			//もしローダを取得できていたら
			if (l) {

				l->Load();	//ロードする

				//ロードが終了したリストに入れる
				MutexLocker m(S().mLoaderListFinishMutex);
				S().mLoaderListFinish.PushBack(l);

				S().LoadEnd();	//ロード終了
			}
			//もしローダが存在しないなら
			else {
				lSleep.SleepSecond(0.1f);	//少し休む
			}

			//スレッドを終了するなら
			if (S().GetEnd(lThreadIndex) == true) {
				break;	//ループを抜ける
			}
		}

		return nullptr;
	}

	#pragma endregion


	//Loaderを登録する
	#pragma region Regist

public:
	void Regist(Loader* aLoader) {
		MutexLocker m(mLoaderListWaitMutex);
		mLoaderListWait.PushBack(aLoader);
	}

private:
	void RegistLoaderNormal(Loader* aLoader) {
		MutexLocker m(mLoaderListNormalMutex);
		mLoaderListNormal.PushBack(aLoader);
	}
	void RegistLoaderHurry(Loader* aLoader) {
		MutexLocker m(mLoaderListHurryMutex);
		mLoaderListHurry.PushBack(aLoader);
	}

	#pragma endregion


	//更新。開始していないLoaderのStart()と、終了したLoaderのFinish()を呼び出す
	#pragma region Update

public:
	void Update() {
		//処理を開始していないローダのStartを呼び出す
		{
			MutexLocker m(mLoaderListWaitMutex);

			while (mLoaderListWait.GetSize() != 0) {
				Loader* l = mLoaderListWait.PopBack();
				StartLoad(l);
			}
		}


		//処理の終わったローダのFinishを呼び出す
		{
			MutexLocker m(mLoaderListFinishMutex);
			for (u32 i = 0; i < mLoaderListFinish.GetSize(); i++) {
				mLoaderListFinish[i]->Finish();
			}
			Delete(mLoaderListFinish);
		}
	}


private:
	void StartLoad(Loader* aLoader) {
		aLoader->Start();
		if (aLoader->IsHurry()) {
			RegistLoaderHurry(aLoader);
		}
		else {
			RegistLoaderNormal(aLoader);
		}
	}

	#pragma endregion


	//ロード中かどうか
	#pragma region IsLoading

public:
	BOOL IsLoading() {
		//LoaderListWaitにローダーが残っていれば、ロード中
		{
			MutexLocker m(mLoaderListWaitMutex);
			if (mLoaderListWait.GetSize() != 0) {
				return true;
			}
		}

		//LoaderListNormalにローダーが残っていれば、ロード中
		{
			MutexLocker m(mLoaderListNormalMutex);
			if (mLoaderListNormal.GetSize() != 0) {
				return true;
			}
		}

		//LoaderListHurryにローダーが残っていれば、ロード中
		{
			MutexLocker m(mLoaderListHurryMutex);
			if (mLoaderListHurry.GetSize() != 0) {
				return true;
			}
		}

		//LoaderListFinishにローダーが残っていれば、ロード中
		{
			MutexLocker m(mLoaderListFinishMutex);
			if (mLoaderListFinish.GetSize() != 0) {
				return true;
			}
		}

		//NowLoadingCountが1以上ならロード中
		{
			MutexLocker m(mNowLoadingCountMutex);
			if (mNowLoadingCount >= 1) {
				return true;
			}
		}

		//どの条件にも当てはまらないなら、ロード中ではない
		return false;
	}

	#pragma endregion


	//フィールド
	#pragma region Field

	//LoaderListとMutex
	#pragma region LoaderList & Mutex

private:
	//処理を開始していないローダのリスト
	Vector<Loader*> mLoaderListWait;
	Mutex mLoaderListWaitMutex;

	//普通の優先度のローダのリスト
	Vector<Loader*> mLoaderListNormal;
	Mutex mLoaderListNormalMutex;

	//優先度の高いローダのリスト
	Vector<Loader*> mLoaderListHurry;
	Mutex mLoaderListHurryMutex;

	//処理の終わったローダのリスト
	Vector<Loader*> mLoaderListFinish;
	Mutex mLoaderListFinishMutex;

	#pragma endregion


	//Threads
	#pragma region Threads

private:
	static constexpr u32 cThreadMaxNum = 5;
	Thread mThread[cThreadMaxNum];

	BOOL GetEnd(u32 aThreadIndex) {
		MutexLocker m(mEndMutex[aThreadIndex]);
		return mEnd[aThreadIndex];
	}
	void SetEnd(u32 aThreadIndex, BOOL aEnd) {
		MutexLocker m(mEndMutex[aThreadIndex]);
		mEnd[aThreadIndex] = aEnd;
	}
	BOOL mEnd[cThreadMaxNum];
	Mutex mEndMutex[cThreadMaxNum];

	#pragma endregion


	//現在ロードしている数
	#pragma region NowLoading

private:
	u32 mNowLoadingCount;
	Mutex mNowLoadingCountMutex;

private:
	void LoadStart() {
		MutexLocker m(mNowLoadingCountMutex);
		mNowLoadingCount++;
	}
	void LoadEnd() {
		MutexLocker m(mNowLoadingCountMutex);
		mNowLoadingCount--;
	}

	#pragma endregion


	#pragma endregion


	//Vectorの要素のデリート
	#pragma region Delete

private:
	static void Delete(Vector<Loader*>& aVector) {
		for (u32 i = 0; i < aVector.GetSize(); i++) {
			delete aVector[i];
		}
		aVector.Clear();
	}

	#pragma endregion

};

}