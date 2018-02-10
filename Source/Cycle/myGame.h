//
//	content	:	ゲーム
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Game/game.h"

namespace myspc {

//Gameの処理を行う基底クラス
class MyGame : public cpot::GameBase {

public:
	//CPOTを初期化する前の段階で呼ばれる。画面サイズなどの設定を行う
	void Setting() override;

	//ゲームの初期化
	void Init() override;

	//ゲームの更新
	void Update() override;

	//ゲームの描画
	void Render() override;
};


}
