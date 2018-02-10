//
//	content	:	コンポーネント
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Game/gameObject.h"

namespace cpot {

class Updater : public Component {
	CPOT_TYPE(Updater, Component)

public:
	Updater();
	~Updater() override;


	//呼び出される関数
	#pragma region Event
public:
	//最初の更新の前に呼び出される
	virtual void OnStart() {}

	//更新処理
	virtual void OnBeforeUpdate() {}
	virtual void OnUpdate() {}
	virtual void OnAfterUpdate() {}

	#pragma endregion


	//優先度
	#pragma region Priority
public:
	virtual s32 GetPriority() {
		return 0;
	}

	#pragma endregion

};

class UpdaterManager : public Singleton<UpdaterManager> {

	friend class Updater;

	//登録&解除。Updaterが呼び出す
	#pragma region Regist&Remove

private:
	void Regist(Updater* aUpdater) {
		mUpdaterNowFrame.PushBack(aUpdater);
	}
	void Remove(Updater* aUpdater) {
		mUpdaterNowFrame.Remove(aUpdater);
		mUpdater.Remove(aUpdater);
	}

public:
	void Clear() {
		mUpdater.Clear();
		mUpdaterNowFrame.Clear();
	}

	#pragma endregion

public:
	void Update() {
		Merge();	//前のフレームに追加されたアップデータを統合する
		Sort();	//優先度順に並び替える
		UpdateUpdater();	//アップデータの更新を呼び出す
	}

private:
	void Merge() {

		//OnStartの呼び出し
		for (u32 i = 0; i < mUpdaterNowFrame.GetSize(); i++) {
			mUpdaterNowFrame[i]->OnStart();
		}

		//統合
		while(mUpdaterNowFrame.GetSize() != 0) {
			mUpdater.PushBack(mUpdaterNowFrame.PopBack());
		}
	}

	void Sort() {
		//優先度によってソートする。
		//本当ならstd::sortでラムダ式を渡してソートしたいが、マルチプラットフォームの為std空間を直接触れないので、自分でバブルソートを実装
		//mUpdater.Sort();

		//降順にソート
		for (u32 i = 0; i < mUpdater.GetSize(); i++) {
			for (u32 j = 0; j < mUpdater.GetSize() - 1; j++) {
				//奥に大きいのがあれば
				if (mUpdater[j]->GetPriority() > mUpdater[j + 1]->GetPriority()) {
					//交換して、大きいのが手前に来るように
					auto tmp = mUpdater[j];
					mUpdater[j] = mUpdater[j + 1];
					mUpdater[j + 1] = tmp;
				}
			}
		}
	}

	void UpdateUpdater() {
		
		for (u32 i = 0; i < mUpdater.GetSize(); i++) {
			mUpdater[i]->OnBeforeUpdate();
		}

		for (u32 i = 0; i < mUpdater.GetSize(); i++) {
			mUpdater[i]->OnUpdate();
		}

		for (u32 i = 0; i < mUpdater.GetSize(); i++) {
			mUpdater[i]->OnAfterUpdate();
		}
	}


private:
	Vector<Updater*> mUpdaterNowFrame;	//新しく追加されたアップデーター
	Vector<Updater*> mUpdater;
};


}