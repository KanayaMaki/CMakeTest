//
//	content	:	OutBaseの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"
#include "./Pot/Usefull/buffer.h"

#include "./Pot/Thread/mutex.h"

namespace cpot {


//アウトのベースクラス
#pragma region OutBase


class OutBase {

	//出力を行う関数
	#pragma region Output

	//可変長テンプレート
public:
	template <typename T, typename... Rest>
	void Output(const T aVal, const Rest... aRest) {
		Output(aVal);
		Output(aRest...);
	}
	template <typename T, typename U>
	void Output(const T aV1, const U aV2) {
		Output(aV1);
		Output(aV2);
	}


	//引数を文字列にして、OutputStrに委譲している
public:
	void Output(const CHAR* aStr) {
		OutputStr(aStr);
	}
	void Output(BOOL aVal) {
		OutputStr(ToString::Do(aVal).Get());
	}
	void Output(s8 aVal) {
		OutputStr(ToString::Do((s32)aVal).Get());
	}
	void Output(u8 aVal) {
		OutputStr(ToString::Do((u32)aVal).Get());
	}
	void Output(s16 aVal) {
		OutputStr(ToString::Do((s32)aVal).Get());
	}
	void Output(u16 aVal) {
		OutputStr(ToString::Do((u32)aVal).Get());
	}
	void Output(s32 aVal) {
		OutputStr(ToString::Do(aVal).Get());
	}
	void Output(u32 aVal) {
		OutputStr(ToString::Do(aVal).Get());
	}
	void Output(s64 aVal) {
		OutputStr(ToString::Do(aVal).Get());
	}
	void Output(u64 aVal) {
		OutputStr(ToString::Do(aVal).Get());
	}
	void Output(f32 aVal) {
		OutputStr(ToString::Do(aVal).Get());
	}
	void Output(f64 aVal) {
		OutputStr(ToString::Do(aVal).Get());
	}
	template<u32 aSize>
	void Output(const String<aSize>& aVal) {
		OutputStr(aVal.Get());
	}
	void Output(const Buffer& aBuffer) {
		OutputByte(aBuffer);
	}

	#pragma endregion


	//派生先でオーバーライドされる
	#pragma region Virtual

public:
	virtual ~OutBase() {}	//仮想デストラクタ

protected:
	virtual void OutputStr(const CHAR* aStr) = 0;	//文字列を出力。必須
	virtual void OutputByte(const Buffer& aBuffer) {}	//バイト列を出力。任意

	#pragma endregion
};


#pragma endregion



//何も出力しないヌルオブジェクト
#pragma region OutNull

class OutNull : public OutBase {
public:
	OutNull() {
		u32 i = 0;
		i++;
	}

private:
	void OutputStr(const CHAR* aStr) override {}

public:
	static OutNull& S() {
		static OutNull s;
		return s;
	}
};

#pragma endregion



//何かのOutputクラスに出力するLog
#pragma region Log

class Log : public OutBase {

	//	TODO	プログラムのどこからでも呼ばれるので、マルチスレッドに対応する

	//初期化を行う
	#pragma region Init

public:
	Log() {
		Reset();
	}

	void Reset() {
		//デフォルトでは、ヌル出力
		mOut = &(OutNull::S());
	}

	#pragma endregion


	//終了処理を行う
	#pragma region Final

public:
	~Log() override {}

	#pragma endregion



	//設定
	#pragma region Setter

public:
	//出力先を設定する
	void Set(OutBase* aOut) {
		mOut = aOut;
	}

	#pragma endregion


	//取得
	#pragma region Getter

public:
	//グローバル的に使用できる、ログのインスタンスを取得
	static Log& S() {
		static Log s;
		return s;
	}

	#pragma endregion


	//操作
	#pragma region Operate

private:
	//文字列を出力する。OutBaseにオーバーライドで呼ばれる
	void OutputStr(const CHAR* aStr) override {
		MutexLocker m(mMutex);
		mOut->Output(aStr);
	}

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	OutBase* mOut;
	Mutex mMutex;

	#pragma endregion
};



#pragma endregion



//Logを出すときに便利なマクロ
#pragma region CPOT_LOG

//ソースコードの中の定数文字列が、馬鹿にならないメモリ量になる気がするので、
//このマクロを使うと消したときに定数文字列がコードに残らない

#ifdef CPOT_VALID_LOG
#define CPOT_LOG(...) \
	cpot::Log::S().Output(__VA_ARGS__, "\n");
#define CPOT_LOG_NO_ENDL(...) \
	cpot::Log::S().Output(__VA_ARGS__);
#else
#define CPOT_LOG(...)
#define CPOT_LOG_NO_ENDL(...)
#endif

#pragma endregion


}