#pragma once

#include "./Pot/Render/OpenGL/Platform/deviceOpenGLPlatform.h"

namespace cpot {

namespace openGL {

namespace platform {

/*


// "renderedTexture"を0番目の付属物としてセットします。
glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

//描画バッファのリストをセットする
GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
glDrawBuffers(1, DrawBuffers); // "1"はDrawBuffersのサイズです。


// 常にフレームバッファがokかをチェックします。
if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
return false;

*/


inline GLenum GetAttachment(u32 aAttachmentNum) {
	switch (aAttachmentNum) {
		case 0:
			return GL_COLOR_ATTACHMENT0;
		case 1:
			return GL_COLOR_ATTACHMENT1;
		case 2:
			return GL_COLOR_ATTACHMENT2;
		case 3:
			return GL_COLOR_ATTACHMENT3;
		case 4:
			return GL_COLOR_ATTACHMENT4;
		case 5:
			return GL_COLOR_ATTACHMENT5;
		case 6:
			return GL_COLOR_ATTACHMENT6;
		case 7:
			return GL_COLOR_ATTACHMENT7;
	}
	CPOT_LOG("アタッチメントは8枚しかできません");
	return GL_COLOR_ATTACHMENT0;
}


class FrameBuffer {

	//初期化・終了処理
	#pragma region Init

public:
	FrameBuffer() {
		Reset();
	}
	~FrameBuffer() {
		Release();
	}
	void Reset() {
		mGLNum = 0;
	}

	#pragma endregion


public:
	void Load() {
		glGenFramebuffers(1, &mGLNum);
	}

	void Release() {
		if (!IsLoaded()) {
			return;	//ロードされていないなら処理しない
		}
		glDeleteFramebuffers(1, &mGLNum);
		Reset();
	}

	void AttachmentColor(GLuint aTexture, u32 aAttachmentNum) {
		glBindFramebuffer(GL_FRAMEBUFFER, mGLNum);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GetAttachment(aAttachmentNum), GL_TEXTURE_2D, aTexture, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void AttachmentDepth(GLuint aTexture) {
		glBindFramebuffer(GL_FRAMEBUFFER, mGLNum);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, aTexture);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void AttachmentStencil(GLuint aTexture) {
		glBindFramebuffer(GL_FRAMEBUFFER, mGLNum);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, aTexture);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void SetDrawBuffer(u32 aDrawBufferNum) {

		glBindFramebuffer(GL_FRAMEBUFFER, mGLNum);
		GLenum lDrawBuffers[8] = { 
			GL_COLOR_ATTACHMENT0,
			GL_COLOR_ATTACHMENT1,
			GL_COLOR_ATTACHMENT2,
			GL_COLOR_ATTACHMENT3,
			GL_COLOR_ATTACHMENT4,
			GL_COLOR_ATTACHMENT5,
			GL_COLOR_ATTACHMENT6,
			GL_COLOR_ATTACHMENT7,
		};
		glDrawBuffers(aDrawBufferNum, lDrawBuffers);
	}

public:
	BOOL IsLoaded() const {
		return mGLNum != 0;
	}

public:
	GLuint GetGLNum() const {
		return mGLNum;
	}

private:
	GLuint mGLNum;
};



}

}

}
