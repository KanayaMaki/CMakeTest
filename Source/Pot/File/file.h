//
//	content	:	Fileの入出力のインターフェース
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"
#include "./Pot/Usefull/buffer.h"

namespace cpot {


//ファイルの最大サイズを格納できる型
using FileSize = u32;


//ファイル出力のベースクラス
#pragma region FileOutBase

class FileOutBase {

	//仮想デストラクタ
	#pragma region Destructor

public:
	CPOT_VI ~FileOutBase() {}

	#pragma endregion


	//ファイルを開く。ファイルを開くのに成功するとtrue、失敗するとfalseを返す
	#pragma region Open

public:
	CPOT_VI BOOL Open(const CHAR* aFileName, BOOL aIsAdd = false, BOOL aBinary = false) CPOT_ZR;

	#pragma endregion

	
	//ファイルを閉じる
	#pragma region Close

public:
	CPOT_VI void Close() CPOT_ZR;
	
	#pragma endregion


	//ファイルに書き込む
	#pragma region Write

public:
	CPOT_VI void Write(const Buffer& aBuffer) CPOT_ZR;
	CPOT_VI void Write(const CHAR* aStr, FileSize aSize) CPOT_ZR;
	CPOT_VI void Write(const CHAR* aStr) CPOT_ZR;

	#pragma endregion

	
	//情報を取得する
	#pragma region Getter

public:
	//ファイルが開かれているか
	CPOT_VI BOOL IsOpen() const CPOT_ZR;

	//ファイルのオープン設定
	CPOT_VI BOOL IsBinary() const CPOT_ZR;

	#pragma endregion

};

#pragma endregion



//ファイル入力のベースクラス
#pragma region FileInBase

class FileInBase {

	//仮想デストラクタ
	#pragma region Destructor

public:
	CPOT_VI ~FileInBase() {}

	#pragma endregion


	//ファイルを開く。ファイルを開くのに成功するとtrue、失敗するとfalseを返す
	#pragma region Open

public:
	CPOT_VI BOOL Open(const CHAR* aFileName, BOOL aBinary = false) CPOT_ZR;

	#pragma endregion


	//ファイルを閉じる
	#pragma region Close

public:
	CPOT_VI void Close() CPOT_ZR;

	#pragma endregion


	//ファイルから読み込む
	#pragma region Read

public:
	CPOT_VI void Read(Buffer& aBuffer) CPOT_ZR;

	#pragma endregion


	//情報を取得する
	#pragma region Getter

public:
	//ファイルが開かれているか
	CPOT_VI BOOL IsOpen() const CPOT_ZR;

	//ファイルのオープン設定
	CPOT_VI BOOL IsBinary() const CPOT_ZR;

	#pragma endregion

};

#pragma endregion

}


#ifdef CPOT_ON_WINDOWS
#include "./Pot/File/Standard/fileStandard.h"
#elif defined CPOT_ON_ANDROID
#include "./Pot/File/Android/fileAndroid.h"
#elif defined CPOT_ON_LINUX
#include "./Pot/File/Standard/fileStandard.h"
#endif