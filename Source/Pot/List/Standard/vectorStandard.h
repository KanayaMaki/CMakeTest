//
//	content	:	StandardでのVectorの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/vector.h"

#include <vector>
#include <algorithm>


namespace cpot {

namespace standard {


//可変長配列のクラス
template <typename T>
class Vector : public VectorBase<T> {

	//要素の追加
	#pragma region Add

public:
	void PushBack(const T& aT) CPOT_OR {
		mVector.push_back(aT);
	}

	#pragma endregion


	//要素の消去
	#pragma region Remove

public:
	//指定された値と等しい要素の削除（１つだけ）
	T Remove(const T& aT) CPOT_OR {
		for (auto it = mVector.begin(); it != mVector.end(); it++) {
			if (*it == aT) {
				T lVal = *it;
				mVector.erase(it);	//要素の削除
				return lVal;
			}
		}
		return mNull;
	}

	//指定された値と等しい要素の削除
	void RemoveAll(const T& aT) CPOT_OR {
		mVector.erase(std::remove(mVector.begin(), mVector.end(), aT), mVector.end());
	}

	//一番最後の要素を削除して返す
	T PopBack() CPOT_OR {
		T lRes = mVector.back();
		mVector.pop_back();
		return lRes;
	}


	//全ての要素を削除
	void Clear() CPOT_OR {
		mVector.clear();
	}

	#pragma endregion


	//要素の取得
	#pragma region Getter

public:
	//インデックスアクセス
	T& operator[](u32 aIndex) CPOT_OR {
		return mVector[aIndex];
	}
	const T& operator[](u32 aIndex) const CPOT_OR {
		return mVector[aIndex];
	}

	//指定された値の要素がいくつあるか
	u32 Count(const T& aT) const CPOT_OR {
		u32 lCount = 0;
		for (auto it = mVector.begin(); it != mVector.end(); it++) {
			if (*it == aT) {
				lCount++;
			}
		}
		return lCount;
	}

	#pragma endregion


	//操作
	#pragma region Operate

public:
	//ソート
	void Sort() CPOT_OR {
		std::sort(mVector.begin(), mVector.end());
	}

	#pragma endregion


	//配列の要素数
	#pragma region Size

public:
	//現在の要素数の取得
	u32 GetSize() const CPOT_OR {
		return mVector.size();
	}

	//現在の要素数を増やす
	void SetSize(u32 aSize) CPOT_OR {
		mVector.resize(aSize);
	}

	#pragma endregion


	//確保しているバッファの要素数
	#pragma region Capacity

public:
	//バッファの要素数を増やす
	void Reserve(u32 aSize) CPOT_OR {
		mVector.reserve(aSize);
	}

	//バッファの要素数を取得
	u32 GetCapacity() const CPOT_OR {
		return mVector.capacity();
	}

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	std::vector<T> mVector;
	static T mNull;

	#pragma endregion
	
};

template <typename T>
T Vector<T>::mNull;


//可変長配列のクラス
template <typename T>
class VectorSimple : public VectorSimpleBase<T> {

	//要素の消去
	#pragma region Remove

public:
	//全ての要素を削除
	void Clear() CPOT_OR {
		mVector.clear();
	}

	#pragma endregion


	//要素の取得
	#pragma region Getter

public:
	//インデックスアクセス
	T& operator[](u32 aIndex) CPOT_OR {
		return mVector[aIndex];
	}
	const T& operator[](u32 aIndex) const CPOT_OR {
		return mVector[aIndex];
	}

	#pragma endregion


	//配列の要素数
	#pragma region Size

public:
	//現在の要素数の取得
	u32 GetSize() const CPOT_OR {
		return mVector.size();
	}

	//現在の要素数を増やす
	void SetSize(u32 aSize) CPOT_OR {
		mVector.resize(aSize);
	}

	#pragma endregion


	//確保しているバッファの要素数
	#pragma region Capacity

public:
	//バッファの要素数を増やす
	void Reserve(u32 aSize) CPOT_OR {
		mVector.reserve(aSize);
	}

	//バッファの要素数を取得
	u32 GetCapacity() const CPOT_OR {
		return mVector.capacity();
	}

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	std::vector<T> mVector;

	#pragma endregion

};


}

template <typename T>
using Vector = standard::Vector<T>;

template <typename T>
using VectorSimple = standard::VectorSimple<T>;

}