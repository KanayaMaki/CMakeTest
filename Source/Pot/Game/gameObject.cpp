//
//	content	:	ゲームオブジェクト
//	author	:	SaitoYoshiki
//

#include "./Pot/Game/gameObject.h"


namespace cpot {

void GameObject::Init(const CHAR* aName) {

	SetName(aName);
	mUnique = UniqueGenerator<GameObject>::S().Generate();

	mFlags.DownAll();
	mFlags.Stand(cActive);

	GameObjectManager::S().Regist(this);
}

GameObject::~GameObject() {
	GameObjectManager::S().Remove(this);
}


GameObject* GameObject::Find(const GameObjectName& aName) {
	return GameObjectManager::S().Find(aName);
}

}
