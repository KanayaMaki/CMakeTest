#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"

namespace cpot {

class Light {
	CPOT_TYPE_BASE(Light)

public:
	virtual ~Light() {}
};

class DirectionalLight : public Light {
	CPOT_TYPE(DirectionalLight, Light)

public:
	DirectionalLight() {
		Reset();
	}

	void Reset() {
		mDirection = -Vector3::One();
	}

public:
	void SetDirection(const Vector3& aDirection) {
		mDirection = aDirection;
	}

	Vector3 GetDirection() const {
		return mDirection;
	}


private:
	Vector3 mDirection;
};


class LightManager : public Singleton<LightManager> {
	friend class Singleton<LightManager>;

public:
	static const u32 cLightMaxNum = 16;

private:
	LightManager() {
		Reset();
	}

public:
	void Reset() {
		for (u32 i = 0; i < cLightMaxNum; i++) {
			mLight[i] = nullptr;
		}
	}

public:
	Light* GetLight() const {
		for (u32 i = 0; i < cLightMaxNum; i++) {
			if (mLight[i] != nullptr) {
				return mLight[i];
			}
		}
		return nullptr;
	}
	Light* GetLight(u32 aIndex) const {
		CPOT_ASSERT(aIndex < cLightMaxNum);
		return mLight[aIndex];
	}

	DirectionalLight* GetDirectionalLight() const {
		for (u32 i = 0; i < cLightMaxNum; i++) {
			Light* l = mLight[i];
			if (l == nullptr) continue;
			if (l->EqualType(DirectionalLight::SGetTypeName())) {
				return (DirectionalLight*)(l);
			}
		}
		return nullptr;
	}


	void SetLight(Light* aLight, u32 aIndex) {
		CPOT_ASSERT(aIndex < cLightMaxNum);
		mLight[aIndex] = aLight;
	}


private:
	Light* mLight[cLightMaxNum];
};


}
