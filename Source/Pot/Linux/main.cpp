#include "Pot/Window/Linux/windowLinux.h"
#include "Pot/Linux/gameMain.h"
#include "./Pot/Out/Standard/outStandard.h"

#include "./Pot/Config/config.h"

int main(int argc , char ** argv) {

    //ログの出力先の初期化
    #ifdef CPOT_VALID_LOG
    cpot::standard::OutStandard lOut;
    cpot::Log::S().Set(&lOut);
    #endif

	//ウィンドウの作成
    cpot::Vector2 lDefaultScreenSize(960.0f, 540.0f);
    cpot::Config::S().SetScreenSize(lDefaultScreenSize);
    cpot::Config::S().SetTitle("CPotGame!");
    cpot::GameMain::Setting();

    cpot::Vector2 lScreenSize = cpot::Config::S().GetScreenSize();
    cpot::linux::Window::S().Init(&argc, argv, lScreenSize, cpot::Config::S().GetTitle());


	//ゲームの初期化
    cpot::GameMain::GameInit();

	glutIdleFunc(cpot::GameMain::GameUpdate);
	glutDisplayFunc(cpot::GameMain::GameRender);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutMainLoop();

	//終了処理
    cpot::GameMain::GameFinal();

    return 0;
}

