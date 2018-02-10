#include "./Pot/Game/lightComponent.h"

namespace cpot {

LightComponent::LightComponent() {
	LightComponentManager::S().Regist(this);
}
LightComponent::~LightComponent() {
	LightComponentManager::S().Remove(this);
}

}