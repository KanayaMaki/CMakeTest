#pragma once

#include "./Pot/Game/updater.h"

#include "./Pot/Render/light.h"

namespace cpot {

class LightComponent : public Updater {
	CPOT_TYPE(LightComponent, Updater)

public:
	LightComponent();
	~LightComponent();

	virtual Light* GetLight() const = 0;
};


class DirectionalLightComponent : public LightComponent {
	CPOT_TYPE(DirectionalLightComponent, LightComponent)

public:
	void OnStart() override {
		mDirection = -Vector3::One();
	}

public:
	void OnUpdate() override {
		mDirectionalLight.SetDirection(GetTransform().mRotation.Rotate(mDirection));
	}

	Light* GetLight() const override {
		return (Light*)(&mDirectionalLight);
	}

public:
	Vector3 GetDirection() const {
		return mDirection;
	}
	void SetDirection(const Vector3& aDirection) {
		mDirection = aDirection;
	}

private:
	Vector3 mDirection;
	DirectionalLight mDirectionalLight;
};
CPOT_REGIST_TYPE(DirectionalLightComponent);


class LightComponentManager : public Updater, public Singleton<LightComponentManager> {
	friend class LightComponent;

private:
	void Regist(LightComponent* l) {
		mLight.PushBack(l);
	}
	void Remove(LightComponent* l) {
		mLight.Remove(l);
	}

public:
	LightComponent* Get(u32 aIndex) {
		return mLight[aIndex];
	}

public:
	void OnUpdate() override {
		for (u32 i = 0; i < mLight.GetSize(); i++) {
			LightManager::S().SetLight(mLight[i]->GetLight(), i);
		}
	}

private:
	Vector<LightComponent*> mLight;
};

}