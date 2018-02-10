//
//	content	:	Hash値で比較する文字列のクラス
//	author	:	SaitoYoshiki
//

#pragma once

#include "string.h"
#include "hash.h"


namespace cpot {


#pragma region 文字列を保存しないHashString

template <u32 cSize>
class HashStringNone {

	//コンストラクタなど
	#pragma region Init

public:
	HashStringNone() {
		Set("");
	}
	HashStringNone(const CHAR* aStr) {
		Set(aStr);
	}

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	HashCode mHashCode;

	#pragma endregion


	//設定
	#pragma region Setter

public:
	void Set(const CHAR* aStr) {
		mHashCode = Hash(aStr);
	}
	const HashStringNone<cSize>& operator =(const CHAR* aStr) {
		Set(aStr);
		return *this;
	}

	#pragma endregion


	//取得
	#pragma region Getter

public:
	HashCode Get() const {
		return mHashCode;
	}
	const CHAR* GetString() const {
		return "";
	}

	#pragma endregion


	//比較
	#pragma region Compare

	//イコール
	#pragma region Equal

public:
	template <u32 cOtherSize>
	BOOL operator ==(const HashStringNone<cOtherSize>& aStr) const {
		return mHashCode == aStr.mHashCode;
	}
	template <u32 cOtherSize>
	BOOL operator !=(const HashStringNone<cOtherSize>& aStr) const {
		return !((*this) == aStr);
	}

	BOOL operator ==(const CHAR* aStr) const {
		return mHashCode == Hash(aStr);
	}
	BOOL operator !=(const CHAR* aStr) const {
		return !((*this) == aStr);
	}

	BOOL operator ==(HashCode aHashCode) const {
		return mHashCode == aHashCode;
	}
	BOOL operator !=(HashCode aHashCode) const {
		return !((*this) == aHashCode);
	}

	#pragma endregion


	//大小関係
	#pragma region Less

public:
	BOOL operator >=(const HashStringNone<cSize>& aStr) const {
		return mHashCode >= aStr.mHashCode;
	}
	BOOL operator <(const HashStringNone<cSize>& aStr) const {
		return !((*this) >= aStr);
	}
	BOOL operator <=(const HashStringNone<cSize>& aStr) const {
		return mHashCode <= aStr.mHashCode;
	}
	BOOL operator >(const HashStringNone<cSize>& aStr) const {
		return !((*this) <= aStr);
	}

	#pragma endregion

	#pragma endregion


	//ハッシュ値を得る関数
	#pragma region Hash

	static const HashCode Hash(const CHAR* aStr) {
		return Hasher::Hash(aStr);
	}

	#pragma endregion
};

#pragma endregion



#pragma region 文字列を保存するHashString


template <u32 cSize>
class HashStringLeft {

	//コンストラクタなど
	#pragma region Init

public:
	HashStringLeft() {
		Set("");
	}
	HashStringLeft(const CHAR* aStr) {
		Set(aStr);
	}

	#pragma endregion


	//フィールド
	#pragma region Field

public:
	using TString = String<cSize>;
	
private:
	TString mString;
	HashCode mHashCode;
	
	#pragma endregion


	//設定
	#pragma region Setter

public:
	void Set(const CHAR* aStr) {
		mHashCode = Hash(aStr);
		mString = aStr;
	}
	const HashStringLeft<cSize>& operator =(const CHAR* aStr) {
		Set(aStr);
		return *this;
	}

	#pragma endregion


	//取得
	#pragma region Getter

public:
	HashCode Get() const {
		return mHashCode;
	}
	const CHAR* GetString() const {
		return mString.Get();
	}

	#pragma endregion


	//比較
	#pragma region Compare

	//イコール
	#pragma region Equal

public:
	template <u32 cOtherSize>
	BOOL operator ==(const HashStringLeft<cOtherSize>& aStr) const {
		return mHashCode == aStr.mHashCode;
	}
	template <u32 cOtherSize>
	BOOL operator !=(const HashStringLeft<cOtherSize>& aStr) const {
		return !((*this) == aStr);
	}

	BOOL operator ==(const CHAR* aStr) const {
		return mHashCode == Hash(aStr);
	}
	BOOL operator !=(const CHAR* aStr) const {
		return !((*this) == aStr);
	}

	BOOL operator ==(HashCode aHashCode) const {
		return mHashCode == aHashCode;
	}
	BOOL operator !=(HashCode aHashCode) const {
		return !((*this) == aHashCode);
	}

	#pragma endregion


	//大小関係
	#pragma region Less

public:
	BOOL operator >=(const HashStringLeft<cSize>& aStr) const {
		return mHashCode >= aStr.mHashCode;
	}
	BOOL operator <(const HashStringLeft<cSize>& aStr) const {
		return !((*this) >= aStr);
	}
	BOOL operator <=(const HashStringLeft<cSize>& aStr) const {
		return mHashCode <= aStr.mHashCode;
	}
	BOOL operator >(const HashStringLeft<cSize>& aStr) const {
		return !((*this) <= aStr);
	}

	#pragma endregion

	#pragma endregion


	//ハッシュ値を得る関数
	#pragma region Hash

	static const HashCode Hash(const CHAR* aStr) {
		return Hasher::Hash(aStr);
	}

	#pragma endregion

};


#pragma endregion



#pragma region どちらのHashStringを使用するかの切り替え


#ifdef CPOT_VALID_HASHSTRING_LEFT

template<s32 cSize>
using HashString = HashStringLeft<cSize>;

#else

template<s32 cSize>
using HashString = HashStringNone<cSize>;

#endif


#pragma endregion



}