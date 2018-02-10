#pragma once

#include "./Pot/Render/OpenGL/Platform/deviceOpenGLPlatform.h"

namespace cpot {

namespace openGL {

namespace platform {


class Depth {
public:
	Depth() {
		Reset();
	}
	~Depth() {
		Release();
	}

protected:
	void Reset() {
		mDepthFunc = GL_LEQUAL;
		mDepthEnable = true;
		mDepthMask = true;
	}


	//ロード
	#pragma region Load

public:
	void Load(BOOL aDepthEnable, GLenum aDepthFunc, BOOL aDepthMask) {
		mDepthEnable = aDepthEnable;
		mDepthFunc = aDepthFunc;
		mDepthMask = aDepthMask;
	}
	void Load() {
		Load(true, GL_LEQUAL, true);
	}
	void LoadTest() {
		Load(true, GL_LEQUAL, true);
	}
	void LoadNoWrite() {
		Load(true, GL_LEQUAL, false);
	}
	void LoadNoTest() {
		Load(false, GL_ALWAYS, false);
	}
	enum CZTestMode {
		cTest,
		cNoWrite,
		cNoTest
	};
	void Load(CZTestMode aMode) {
		switch (aMode) {
			case cTest:
				LoadTest();
				break;
			case cNoWrite:
				LoadNoWrite();
				break;
			case cNoTest:
				LoadNoTest();
				break;
		}
	}

	#pragma endregion



	void Release() {
		Reset();
	}
	void SetToDevice() {

		//Zテストを行うかの設定
		if (mDepthEnable) {
			glEnable(GL_DEPTH_TEST);

			//Zテストに使う関数の設定
			glDepthFunc(mDepthFunc);
		}
		else {
			glDisable(GL_DEPTH_TEST);
		}

		//Z値をZバッファに書き込むかの設定
		if (mDepthMask) {
			glDepthMask(true);
		}
		else {
			glDepthMask(false);
		}
	}


public:
	BOOL IsLoaded() const {
		return true;
	}

	BOOL GetDepthEnable() const {
		return mDepthEnable;
	}

	BOOL GetDepthMask() const {
		return mDepthMask;
	}
	GLenum GetDepthFunc() const {
		return mDepthFunc;
	}

protected:
	BOOL mDepthEnable;
	GLenum mDepthFunc;
	BOOL mDepthMask;
};


}

}

}
