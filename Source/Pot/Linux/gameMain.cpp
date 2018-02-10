//
//	content	:	エントリーポイント
//	author	:	SaitoYoshiki
//

#include "./Pot/Linux/gameMain.h"
#include "./Pot/Game/game.h"

#include "./Pot/Render/OpenGL/Platform/deviceOpenGLPlatform.h"
#include "./Pot/Out/Standard/outStandard.h"

#include "./Pot/Config/config.h"

#include "./Pot/Time/time.h"
#include "./Pot/Loader/loader.h"

#include "./Pot/Usefull/resourceUpdaterList.h"

namespace cpot {


GameBase* GameMain::mGame;
Time gTime;
f64 gBeforeTime;

void GameMain::Setting() {
	mGame = cpot::CreateGame();
	mGame->Setting();
}

void GameMain::GameInit() {

	//プラットフォームの初期化
	#pragma region PlatformInit

	openGL::platform::Device::S().Init();


	//ウィンドウズの入力の初期化

	//ゲームの初期化
	mGame->Init();

	gBeforeTime = gTime.GetDetail();
}

void GameMain::GameUpdate() {

	//InputUpdate
	f64 lNowTime = gTime.GetDetail();
	SetDeltaTime(lNowTime - gBeforeTime);
	gBeforeTime = lNowTime;

	//ローダのアップデート
	LoaderManager::S().Update();
		
	//リソースのアップデート
	ResourceUpdaterList::S().Update();

	//ゲームの更新
	mGame->Update();

	//ゲームの終了
	if (Config::S().GetApplicationEnd() || Config::S().GetGameEnd()) {
		LoaderManager::S().Join();
		glutLeaveMainLoop();
	}

	glutPostRedisplay();
}

void GameMain::GameRender() {
	//ゲームの描画
	mGame->Render();
}
void GameMain::GameFinal() {
	openGL::platform::Device::S().Final();
}

}
