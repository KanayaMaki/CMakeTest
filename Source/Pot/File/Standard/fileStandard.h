//
//	content	:	StandardでのFileの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/File/file.h"

#include <fstream>
#include <vector>

namespace cpot {

namespace standard {


//ファイル出力のクラス
#pragma region FileOut

class FileOut : public FileOutBase {

	//コンストラクタ
	#pragma region Constructor

public:
	FileOut() {
		
	}
	FileOut(const CHAR* aFileName, BOOL aIsAdd = false, BOOL aBinary = false) {
		Open(aFileName, aIsAdd, aBinary);
	}

	#pragma endregion
	

	//デストラクタ
	#pragma region Destructor

	~FileOut() CPOT_OR {
		Close();
	}

	#pragma endregion


	//ファイルを開く。ファイルを開くのに成功するとtrue、失敗するとfalseを返す
	#pragma region Open

public:
	BOOL Open(const CHAR* aFileName, BOOL aIsAdd = false, BOOL aBinary = false) CPOT_OR {
		std::ios_base::openmode lOpenMode = std::ios::out;
		if (aIsAdd) {
			lOpenMode |= std::ios::app;
		}
		else {
			lOpenMode |= std::ios::trunc;
		}
		if (aBinary) {
			lOpenMode |= std::ios::binary;
			mIsBinary = true;
		}
		else {
			mIsBinary = false;
		}

		mOfs.open(aFileName, lOpenMode);

		return IsOpen();
	}

	#pragma endregion


	//ファイルを閉じる
	#pragma region Close

public:
	void Close() CPOT_OR {
		mOfs.close();
	}

	#pragma endregion


	//ファイルに書き込む
	#pragma region Write

public:
	void Write(const Buffer& aBuffer) CPOT_OR {
		mOfs.write((const CHAR*)(aBuffer.Get()), aBuffer.GetSize());
	}
	void Write(const CHAR* aStr, FileSize aSize) CPOT_OR {
		mOfs.write(aStr, aSize);
	}
	void Write(const CHAR* aStr) CPOT_OR {
		mOfs.write(aStr, StringLen(aStr));
	}

	#pragma endregion


	//情報を取得する
	#pragma region Getter

public:
	//ファイルが開かれているか
	BOOL IsOpen() const CPOT_OR {
		return (!mOfs) == false;
	}

	//ファイルのオープン設定
	BOOL IsBinary() const CPOT_OR {
		return mIsBinary;
	}

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	std::ofstream mOfs;
	BOOL mIsBinary;

	#pragma endregion

};

#pragma endregion



//ファイル入力のベースクラス
#pragma region FileIn

class FileIn : public FileInBase {

	//コンストラクタ
	#pragma region Constructor

public:
	FileIn() {}
	FileIn(const CHAR* aFileName, BOOL aBinary = false) {
		Open(aFileName, aBinary);
	}

	#pragma endregion


	//デストラクタ
	#pragma region Destructor

public:
	~FileIn() {
		Close();
	}

	#pragma endregion


	//ファイルを開く。ファイルを開くのに成功するとtrue、失敗するとfalseを返す
	#pragma region Open

public:
	BOOL Open(const CHAR* aFileName, BOOL aBinary = false) CPOT_OR {
		std::ios_base::openmode lOpenMode= std::ios::in;
		if (aBinary) {
			lOpenMode |= std::ios::binary;
			mIsBinary = true;
		}
		else {
			mIsBinary = false;
		}

		mIfs.open(aFileName, lOpenMode);

		return IsOpen();
	}

	#pragma endregion


	//ファイルを閉じる
	#pragma region Close

public:
	void Close() CPOT_OR {
		mIfs.close();
	}

	#pragma endregion


	//ファイルから読み込む
	//現在のPositionから読み込む
	#pragma region Read

public:
	void Read(Buffer& aBuffer) CPOT_OR {
		
		std::istreambuf_iterator<char> lTt(mIfs);
		std::istreambuf_iterator<char> lLast;
		std::vector<char> lStr(lTt, lLast);

		aBuffer.Load((const BYTE*)lStr.data(), lStr.size());
	}

	#pragma endregion


	//情報を取得する
	#pragma region Getter

public:
	//ファイルが開かれているか
	BOOL IsOpen() const CPOT_OR {
		return (!mIfs.fail());
	}

	//ファイルのオープン設定
	BOOL IsBinary() const CPOT_OR {
		return mIsBinary;
	}

	#pragma endregion


	//フィールド
	#pragma region Field

private:
	std::ifstream mIfs;
	BOOL mIsBinary;

	#pragma endregion
};

#pragma endregion


}

using FileOut = standard::FileOut;
using FileIn = standard::FileIn;

}