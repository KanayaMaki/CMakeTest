#pragma once

#include "./Pot/Game/updater.h"

#include "./Pot/Render/camera.h"

namespace cpot {

class CameraComponent : public Updater {
	CPOT_TYPE(CameraComponent, Updater)

public:
	CameraComponent();
	~CameraComponent();

	virtual Matrix4x4 GetViewMatrix() const = 0;
	virtual Matrix4x4 GetProjectionMatrix() const = 0;

	virtual Camera* GetCamera() const = 0;
};


class PersCameraComponent : public CameraComponent {
	CPOT_TYPE(PersCameraComponent, CameraComponent)

public:
	void OnUpdate() override {
		mPersCamera.mView.SetLocation(GetTransform().mPosition);
		mPersCamera.mView.SetRotation(GetTransform().mRotation);
	}

	Matrix4x4 GetViewMatrix() const override {
		return mPersCamera.mView.GetMatrix();
	}
	Matrix4x4 GetProjectionMatrix() const override {
		return mPersCamera.mProjection.GetMatrix();
	}

	Camera* GetCamera() const override {
		return (Camera*)(&mPersCamera);
	}

public:
	PersCamera mPersCamera;
};
CPOT_REGIST_TYPE(PersCameraComponent);


class CameraComponentManager : public Updater, public Singleton<CameraComponentManager> {
	friend class CameraComponent;

private:
	void Regist(CameraComponent* l) {
		mCamera.PushBack(l);
	}
	void Remove(CameraComponent* l) {
		mCamera.Remove(l);
	}

public:
	CameraComponent* Get(u32 aIndex) {
		return mCamera[aIndex];
	}

public:
	void OnUpdate() override {
		for (u32 i = 0; i < mCamera.GetSize(); i++) {
			CameraManager::S().SetCamera(mCamera[i]->GetCamera(), i);
		}
	}

private:
	Vector<CameraComponent*> mCamera;
};

}