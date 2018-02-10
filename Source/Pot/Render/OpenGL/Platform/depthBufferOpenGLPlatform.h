#pragma once

#include "./Pot/Render/OpenGL/Platform/deviceOpenGLPlatform.h"


namespace cpot {

namespace openGL {

namespace platform {

/*

glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mNum);


描画されたテクスチャを使うときにデプスが必要な場合があるかもしれません。その場合には、以下のように作られたテクスチャに単純に描画するだけです。
glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT24, 1024, 768, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);


*/



class DepthBuffer {

public:
	void Load(u32 aWidth, u32 aHeight) {
		
		//デプスバッファを割り当てる
		glGenRenderbuffers(1, &mNum);
		glBindRenderbuffer(GL_RENDERBUFFER, mNum);

		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, aWidth, aHeight);

		//データの設定
		mWidth = aWidth;
		mHeight = aHeight;
	}

	void Release() {

		//ロード済みなら解放しない
		if (IsLoaded()) {
			return;
		}

		//テクスチャの解放
		glDeleteRenderbuffers(1, &mNum);
	}

public:
	BOOL IsLoaded() const {
		return mNum != 0;
	}

	GLuint Num() const {
		return mNum;
	}


private:
	GLuint mNum;
	u32 mWidth;
	u32 mHeight;
};


}

}

}
