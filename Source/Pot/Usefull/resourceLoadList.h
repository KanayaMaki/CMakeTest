//
//	content	:	事前に登録しておいた文字列を、キーから取得する
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/hashTable.h"

namespace cpot {

template <typename T, typename DataType>
class ResourceLoadList  : public Singleton<ResourceLoadList<T, DataType>> {
	friend class Singleton<ResourceLoadList<T, DataType>>;

public:
	//登録
	#pragma region Regist

public:
	void Regist(const HashTableKey& aKey, const DataType& aData) {
		mDataList.Add(aKey, aData);
	}

	#pragma endregion


	//取得
	#pragma region Get

public:
	const DataType& Get(const HashTableKey& aKey) {
		if (mDataList.Exist(aKey)) {
			return mDataList[aKey];
		}
		return mNullData;
	}
	const DataType& Get(const CHAR* aKey) {
		return Get(HashTableKey(aKey));	//委譲
	}

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	HashTable<DataType> mDataList;	//キーと名前のセット
	static DataType mNullData;

	#pragma endregion
};

template <typename T, typename DataType>
DataType ResourceLoadList<T, DataType>::mNullData;

}