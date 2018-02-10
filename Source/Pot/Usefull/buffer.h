//
//	content	:	バッファクラスの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

namespace cpot {

using BufferSize = u32;

class Buffer {
	
	//コンストラクタなど
	#pragma region Constructor

public:
	Buffer() {
		Reset();
	}
	Buffer(const BYTE* aBuffer, BufferSize aSize) {
		Reset();
		Load(aBuffer, aSize);
	}

	Buffer(const CHAR* aStr) {
		Reset();
		Load(aStr);
	}
	const Buffer& operator=(const Buffer& aB) {
		Reset();
		Load(aB.mBuffer, aB.mSize);
		return (*this);
	}
	Buffer(const Buffer& aB) {
		Reset();
		Load(aB.mBuffer, aB.mSize);
	}


	void Reset() {
		mBuffer = nullptr;
		mSize = 0;
		mCapacity = 0;
		mPosition = 0;
	}

	#pragma endregion


	//デストラクタなど
	#pragma region Destructor

	~Buffer() {
		Release();
	}

	void Release() {
		if (IsLoaded()) {
			delete[] mBuffer;
			Reset();
		}
	}

	#pragma endregion


	//作成
	#pragma region Create

	void Load(const BYTE* aBuffer, BufferSize aSize) {

		Release();

		if (aSize > 0) {
			mBuffer = new BYTE[aSize];
			CopyMem(&(mBuffer[0]), &(aBuffer[0]), aSize);
			mSize = aSize;
			mCapacity = aSize;
		}
	}
	void Load(const CHAR* aStr) {
		Load((const BYTE*)aStr, StringLen(aStr));
	}

	void Create(BufferSize aSize) {

		Release();

		if (aSize > 0) {
			mBuffer = new BYTE[aSize];
			ZeroMem(&(mBuffer[0]), aSize);
			mSize = aSize;
			mCapacity = aSize;
		}
	}

	#pragma endregion


	//取得
	#pragma region Getter

	//バッファ
	BYTE* Get() const {
		return mBuffer;
	}

	//インデックスアクセス
	BYTE& operator[](u32 aIndex) {
		CPOT_ASSERT(aIndex < mSize);
		return mBuffer[aIndex];
	}
	BYTE operator[](u32 aIndex) const {
		CPOT_ASSERT(aIndex < mSize);
		return mBuffer[aIndex];
	}

	//データのサイズ
	BufferSize GetSize() const {
		return mSize;
	}

	//バッファのサイズ
	BufferSize GetCapacity() const {
		return mCapacity;
	}

	//バッファのカーソルの現在位置
	BufferSize GetPosition() const {
		return mPosition;
	}

	//読み込み済みかどうか
	BOOL IsLoaded() const {
		return mBuffer != nullptr;
	}

	#pragma endregion


	//設定
	#pragma region Setter

	//現在位置を設定する
	void SetPosition(BufferSize aPosition) {
		mPosition = Clamp(aPosition, BufferSize(0), mSize - 1);
	}

	#pragma endregion
	

	//操作
	#pragma region Operation

	//バッファからデータを読み込む
	BufferSize Read(void* aBuffer, BufferSize aSize) {
		
		if (IsLoaded() == false) {
			return 0;
		}
		CPOT_ASSERT(aSize >= 0);

		BufferSize lEnd = mPosition + aSize;
		if (GetSize() < lEnd) {
			lEnd = GetSize();
		}
		BufferSize lReadSize = lEnd - mPosition;

		CopyMem(aBuffer, &(mBuffer[mPosition]), lReadSize);
		mPosition += lReadSize;

		return lReadSize;
	}

	void Read(Buffer& aBuffer, BufferSize aSize) {

		if (IsLoaded() == false) {
			return;
		}
		CPOT_ASSERT(aSize >= 0);

		BufferSize lEnd = mPosition + aSize;
		if (GetSize() < lEnd) {
			lEnd = GetSize();
		}
		BufferSize lReadSize = lEnd - mPosition;

		aBuffer.Load(&mBuffer[mPosition], lReadSize);
		mPosition += lReadSize;
	}

	template<typename T>
	T Read() {
		T t;
		Read(&t, sizeof(T));
		return t;
	}


	void Add(const BYTE* aBuffer, BufferSize aSize) {

		//新しいバッファのサイズの計算
		BufferSize lNewSize = mSize + aSize;
		//新しいバッファの作成
		Reserve(lNewSize);

		//追加するバッファのデータをコピー
		CopyMem(&mBuffer[mSize], aBuffer, aSize);
		mSize = lNewSize;
	}
	void Add(const Buffer& aBuffer) {
		Add(aBuffer.mBuffer, aBuffer.GetSize());
	}

	template<typename T>
	void Add(const T* aBuffer) {
		Add((const BYTE*)(aBuffer), sizeof(T));
	}

	void Reserve(BufferSize aCapacity) {
		
		BufferSize lNewCapacity = Max(32, mCapacity);
		
		//バッファサイズが足りなくなる場合
		if (mCapacity < aCapacity) {

			//バッファサイズを計算する
			while (lNewCapacity < aCapacity) {
				lNewCapacity *= 2;
			}

			BYTE* lNewBuffer = new BYTE[lNewCapacity];

			//前のバッファのデータをコピー
			CopyMem(lNewBuffer, mBuffer, mSize);

			//現在のバッファを削除
			delete[] mBuffer;
			mBuffer = lNewBuffer;
			mCapacity = lNewCapacity;
		}
		//現在のバッファサイズで十分な場合
		else {

		}
	}

	#pragma endregion


	//データ
	#pragma region Data

public:
	template <typename T>
	void LoadData(const T& aData) {
		Load((const BYTE*)(&aData), sizeof(T));
	}

	template <typename T>
	T* GetData() {
		return (T*)(mBuffer);
	}

	#pragma endregion



	//フィールド
	#pragma region Field

private:
	BYTE* mBuffer;
	BufferSize mCapacity;
	BufferSize mSize;
	BufferSize mPosition;

	#pragma endregion
};


}