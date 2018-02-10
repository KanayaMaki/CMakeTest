//
//	content	:	ゲームのコンフィグのインターフェース
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"

namespace cpot {


//ファイル出力のベースクラス
#pragma region ConfigBase

class ConfigBase {

	//仮想デストラクタ
	#pragma region Destructor

public:
	CPOT_VI ~ConfigBase() {}

	#pragma endregion


	//画面サイズ
	#pragma region ScreenSize

public:
	CPOT_VI void SetScreenSize(const Vector2& aScreenSize) CPOT_ZR;
	CPOT_VI Vector2 GetScreenSize() CPOT_ZR;

	#pragma endregion


	//アプリケーションが終了するかどうか
	#pragma region ApplicationEnd

public:
	CPOT_VI void SetApplicationEnd() CPOT_ZR;
	CPOT_VI BOOL GetApplicationEnd() CPOT_ZR;

	#pragma endregion


	//ゲームが終了するかどうか
	#pragma region GameEnd

	CPOT_VI void SetGameEnd() CPOT_ZR;
	CPOT_VI BOOL GetGameEnd() CPOT_ZR;

	#pragma endregion

	
	//ゲームタイトルの設定
	#pragma region Title

	CPOT_VI const CHAR* GetTitle() CPOT_ZR;
	CPOT_VI void SetTitle(const CHAR* aTitle) CPOT_ZR;

	#pragma endregion

	
	//ゲームがアクティブかどうか
	#pragma region Active

	CPOT_VI void SetIsActive(BOOL aIsActive) CPOT_ZR;
	CPOT_VI BOOL GetIsActive() CPOT_ZR;

	#pragma endregion


	//ゲームのFPS
	#pragma region Fps

	CPOT_VI void SetFps(f32 aFps) CPOT_ZR;
	CPOT_VI f32 GetFps() CPOT_ZR;

	#pragma endregion
	
protected:
	Vector2 mScreenSize;
	String<64> mTitle;
	BOOL mApplicationEnd;
	BOOL mGameEnd;
	BOOL mActive;
	f32 mFps;
};

#pragma endregion


}


#ifdef CPOT_ON_LINUX
#include "./Pot/Config/Linux/configLinux.h"
#elif defined CPOT_ON_ANDROID
#include "./Pot/Config/Android/configAndroid.h"
#elif defined CPOT_ON_WINDOWS
#include "./Pot/Config/Windows/configWindows.h"
#endif