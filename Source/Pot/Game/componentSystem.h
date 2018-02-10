//
//	content	:	ゲームオブジェクト
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Game/component.h"
#include "./Pot/Game/gameObject.h"
#include "./Pot/Game/updater.h"
#include "./Pot/Game/renderer.h"

namespace cpot {

class ComponentSystem : public Singleton<ComponentSystem> {
public:
	void Update() {
		UpdaterManager::S().Update();
		RendererManager::S().Update();
		ComponentManager::S().Update();
		GameObjectManager::S().Update();
	}

	void Render() {
		RendererManager::S().Render();
	}
};

}
