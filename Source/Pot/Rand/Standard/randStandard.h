//
//	content	:	Standardでの乱数を生成するクラスの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Rand/rand.h"

#include <random>

namespace cpot {

namespace standard {

#undef max
#undef min


//64bitの乱数を生成するデバイス
class Rand64Device {

	//初期化
	#pragma region Init

public:
	Rand64Device() {
		Reset();
	}

	void Reload() {
		SetSeed(mSeed);
	}
	void Reset() {
		SetSeed(0);
	}

	#pragma endregion


	//取得
	#pragma region Getter

public:
	//MinValue() <= x, x <= MaxValue()の乱数を生成
	u64 Next() {
		return mMt();
	}


	//シード値を取得
	u64 GetSeed() const {
		return mSeed;
	}

	//乱数の最大値
	u64 MaxValue() const {
		return mMt.max();
	}

	//乱数の最小値
	u64 MinValue() const {
		return mMt.min();
	}

	#pragma endregion


	//設定
	#pragma region Setter

	void SetSeed(u64 aSeed) {
		mMt.seed(aSeed);
		mSeed = aSeed;

		//最初は偏るので、読み飛ばす
		for (u32 i = 0; i < 100; i++) {
			Next();
		}
	}

	#pragma endregion

	
	//フィールド
	#pragma region Field

private:
	std::mt19937_64 mMt;	//メルセンヌツイスタで64bitの乱数を生成するデバイス
	u64 mSeed;	//シード値

	#pragma endregion
};


//32bitの乱数を生成するデバイス
class Rand32Device {

	//初期化
	#pragma region Init

public:
	Rand32Device() {
		Reset();
	}

	void Reload() {
		SetSeed(mSeed);
	}
	void Reset() {
		SetSeed(0);
	}

	#pragma endregion


	//取得
	#pragma region Getter

public:
	//MinValue() <= x, x <= MaxValue()の乱数を生成
	u32 Next() {
		return mMt();
	}


	//シード値を取得
	u32 GetSeed() const {
		return mSeed;
	}

	//乱数の最大値
	u32 MaxValue() const {
		return mMt.max();
	}

	//乱数の最小値
	u32 MinValue() const {
		return mMt.min();
	}

	#pragma endregion


	//設定
	#pragma region Setter

	void SetSeed(u32 aSeed) {
		mMt.seed(aSeed);
		mSeed = aSeed;

		//最初は偏るので、読み飛ばす
		for (u32 i = 0; i < 100; i++) {
			Next();
		}
	}

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	std::mt19937 mMt;	//メルセンヌツイスタで64bitの乱数を生成するデバイス
	u32 mSeed;	//シード値

	#pragma endregion
};


//RandBaseを派生した乱数を生成するクラス
class Rand : public RandBase {

	//初期化
	#pragma region Init

public:
	Rand() {
		Reset();
	}

	#pragma endregion


	//取得
	#pragma region Getter

private:
	//乱数を生成する
	RandType NextInner() override {
		return mRand.Next();
	}

	//乱数の最大値
	RandType MaxValueInner() const override {
		return mRand.MaxValue();
	}
	//乱数の最小値
	RandType MinValueInner() const override {
		return mRand.MinValue();
	}

	//現在のシード値の取得
	SeedType GetSeedInner() const override {
		return mRand.GetSeed();
	}

	#pragma endregion


	//設定
	#pragma region Setter

private:
	//シード値を設定
	void SetSeedInner(SeedType aSeed) override {
		mRand.SetSeed(aSeed);
	}

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	Rand32Device mRand;

public:
	Rand32Device GetDevice() const {
		return mRand;
	}

	#pragma endregion

};


}

using Rand = standard::Rand;

}