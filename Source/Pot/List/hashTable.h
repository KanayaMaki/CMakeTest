//
//	content	:	HashTableのインターフェース
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

namespace cpot {

using HashTableKey = HashString<32>;

//ハッシュテーブルのクラス
template <typename T>
class HashTableBase {

	//要素の追加
	#pragma region Add

public:
	// ! 同じキーがすでにある場合、追加しない
	CPOT_VI void Add(const HashTableKey& aKey, T aValue) CPOT_ZR;

	#pragma endregion


	//要素の消去
	#pragma region Remove

public:
	//指定されたキーを持つ要素の削除
	CPOT_VI T Remove(const HashTableKey& aKey) CPOT_ZR;

	//指定された値と等しい要素の削除
	CPOT_VI void Remove(T aT) CPOT_ZR;

	//全ての要素を削除
	CPOT_VI void Clear() CPOT_ZR;

	#pragma endregion


	//要素の取得
	#pragma region Getter

public:
	//インデックスアクセス
	// ! 要素がなければ、作成する
	CPOT_VI T& operator[](const HashTableKey& aKey) CPOT_ZR;

	//名前で検索
	// ! 要素がなければ0を返す
	CPOT_VI T Find(const HashTableKey& aKey) const CPOT_ZR;

	//指定されたキーを持つ要素が存在するか
	CPOT_VI BOOL Exist(const HashTableKey& aKey) const CPOT_ZR;

	#pragma endregion


	//要素の設定
	#pragma region Setter

public:
	CPOT_VI void Set(const HashTableKey& aKey, const T& aValue) CPOT_ZR;

	#pragma endregion


	//配列の要素数
	#pragma region Size

public:
	//現在の要素数の取得
	CPOT_VI u32 GetSize() const CPOT_ZR;

	#pragma endregion
};


}


#ifdef CPOT_ON_WINDOWS
#include "./Pot/List/Standard/hashTableStandard.h"
#elif defined CPOT_ON_ANDROID
#include "./Pot/List/Android/hashTableAndroid.h"
#elif defined CPOT_ON_LINUX
#include "./Pot/List/Standard/hashTableStandard.h"
#endif