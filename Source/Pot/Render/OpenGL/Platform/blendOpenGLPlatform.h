#pragma once

#include "./Pot/Render/OpenGL/Platform/deviceOpenGLPlatform.h"


namespace cpot {

namespace openGL {

namespace platform {


/*

アルファブレンド
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
反転
glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
加算
glBlendFunc(GL_ONE, GL_ONE);
加算+アルファ(PhotoShop的スクリーン)
glBlendFunc(GL_SRC_ALPHA, GL_ONE);
スクリーン(PhotoShop的 比較(明))
glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE);
乗算
glBlendFunc(GL_ZERO, GL_SRC_COLOR);
乗算+アルファ
dst = dst * src * alpha
= (dst * src) * alpha
glBlendFunc(GL_ZERO, GL_SRC_COLOR);
glBlendFunc(GL_ZERO, GL_SRC_ALPHA);



*/


class Blend {
public:
	Blend() {
		Reset();
	}
	~Blend() {
		Release();
	}

protected:
	void Reset() {
		mSrc = GL_SRC_ALPHA;
		mDst = GL_ONE_MINUS_SRC_ALPHA;
	}

	//ロード
	#pragma region Load

public:
	void Load(GLenum aSrc, GLenum aDst) {
		mSrc = aSrc;
		mDst = aDst;
	}

	void LoadNormal() {
		Load(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	void LoadAdd() {
		Load(GL_SRC_ALPHA, GL_ONE);
	}
	void LoadScreen() {
		Load(GL_ONE_MINUS_DST_COLOR, GL_ONE);
	}
	void LoadMulti() {
		Load(GL_ZERO, GL_SRC_COLOR);
	}

	enum CBlendMode {
		cNormal,
		cAdd,
		cScreen,
		cMulti
	};
	void Load(CBlendMode aMode) {
		switch (aMode) {
			case cNormal:
				LoadNormal();
				break;
			case cAdd:
				LoadAdd();
				break;
			case cScreen:
				LoadScreen();
				break;
			case cMulti:
				LoadMulti();
				break;
		}
	}

	#pragma endregion


public:
	void Release() {
		Reset();
	}


public:
	void SetToDevice() {
		glEnable(GL_BLEND);
		glBlendFunc(mSrc, mDst);
	}


public:
	BOOL IsLoaded() const {
		return true;
	}

	GLenum GetSrc() const {
		return mSrc;
	}

	GLenum GetDst() const {
		return mDst;
	}

protected:
	GLenum mSrc;
	GLenum mDst;
};


}

}

}
