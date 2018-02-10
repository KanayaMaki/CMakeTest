#include "./Pot/Game/cameraComponent.h"

namespace cpot {

CameraComponent::CameraComponent() {
	CameraComponentManager::S().Regist(this);
}
CameraComponent::~CameraComponent() {
	CameraComponentManager::S().Remove(this);
}

}