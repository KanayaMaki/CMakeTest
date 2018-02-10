//
//	content	:	StandardでのHashTableの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/hashTable.h"

#include <map>

namespace cpot {

namespace standard {


//ハッシュテーブルのクラス
template <typename T>
class HashTable : public HashTableBase<T> {

	//要素の追加
	#pragma region Add

public:
	// ! 同じキーがすでにある場合、追加しない
	void Add(const HashTableKey& aKey, T aValue) CPOT_OR {
		mList.insert(std::make_pair(aKey, aValue));
	}

	#pragma endregion


	//要素の消去
	#pragma region Remove

public:
	//指定されたキーを持つ要素の削除
	T Remove(const HashTableKey& aKey) CPOT_OR {
		auto it = mList.find(aKey);

		//要素があれば
		if (it != mList.end()) {
			T tRes = (*it).second;
			mList.erase(it);
			return tRes;
		}
		return mNull;
	}

	//指定された値と等しい要素の削除
	void Remove(T aT) CPOT_OR {

	}

	//全ての要素を削除
	void Clear() CPOT_OR {
		mList.clear();
	}

	#pragma endregion


	//要素の取得
	#pragma region Getter

public:
	//インデックスアクセス
	// ! 要素がなければ、作成する
	T& operator[](const HashTableKey& aKey) CPOT_OR {
		return mList[aKey];
	}

	//名前で検索
	// ! 要素がなければ0を返す
	T Find(const HashTableKey& aKey) const CPOT_OR {
		auto it = mList.find(aKey);
		if (it != mList.end()) {
			return (*it).second;
		}
		return mNull;
	}


	//指定されたキーを持つ要素が存在するか
	BOOL Exist(const HashTableKey& aKey) const CPOT_OR {
		return mList.find(aKey) != mList.end();
	}

	#pragma endregion


	//要素の設定
	#pragma region Setter

public:
	void Set(const HashTableKey& aKey, const T& aValue) CPOT_OR {
		CPOT_ASSERT(Exist(aKey));	//すでに要素が存在していなければいけない
		mList[aKey] = aValue;
	}

	#pragma endregion

	//配列の要素数
	#pragma region Size

public:
	//現在の要素数の取得
	u32 GetSize() const CPOT_OR {
		return mList.size();
	}

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	std::map<HashTableKey, T> mList;
	static T mNull;

	#pragma endregion

};

template <typename T>
T HashTable<T>::mNull;

}

template <typename T>
using HashTable = standard::HashTable<T>;

}