//
//	content	:	コンポーネント
//	author	:	SaitoYoshiki
//

#include "./Pot/Game/component.h"
#include "./Pot/Game/unique.h"

#include "./Pot/Game/gameObject.h"

namespace cpot {

Component::Component() {
	ComponentManager::S().Regist(this);
}

Component::~Component() {
	ComponentManager::S().Remove(this);
}



void Component::InitComponent(GameObject* aGameObject) {

	//ユニークな番号の取得
	mUnique = UniqueGenerator<Component>::S().Generate();

	//ゲームオブジェクトの設定
	mGameObject = aGameObject;

	//フラグのリセット
	mFlags.AllBitDown();
	mFlags.Stand(cActive);

	if (mGameObject->GetActive()) {
		mFlags.Stand(cGameObjectActive);
	}
}

}