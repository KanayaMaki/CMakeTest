//
//	content	:	ゲーム
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

namespace cpot {

//Gameの処理を行う基底クラス
class GameBase {

public:
	//仮想デストラクタ
	virtual ~GameBase() {}

	//CPOTを初期化する前の段階で呼ばれる。画面サイズなどの設定を行う
	virtual void Setting() = 0;

	//ゲームの初期化
	virtual void Init() = 0;

	//ゲームの更新
	virtual void Update() = 0;

	//ゲームの描画
	virtual void Render() = 0;
};

//ユーザーが実装する必要がある
GameBase* CreateGame();

}
