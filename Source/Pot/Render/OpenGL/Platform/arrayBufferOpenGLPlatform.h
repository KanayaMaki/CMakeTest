#pragma once

#include "./Pot/Render/OpenGL/Platform/bufferOpenGLPlatform.h"


namespace cpot {

namespace openGL {

namespace platform {

/*
glBindFramebufferの2番目のパラメータを0にすることで実行されます。

// スクリーンに描画する。
glBindFramebuffer(GL_FRAMEBUFFER, 0);
glViewport(0,0,1024,768); //フレームバッファ全体に描画する。左下隅から右上隅へ。

*/



class ArrayBuffer : public Buffer {
public:
	void Load(u32 aVertexSize, u32 aVertexNum, const void* aInitData, GLenum aUsage) {
		mVertexNum = aVertexNum;
		mVertexSize = aVertexSize;
		Buffer::Load(GL_ARRAY_BUFFER, aVertexSize * aVertexNum, aInitData, aUsage);
	}

	void Load(u32 aVertexSize, u32 aVertexNum, const void* aInitData) {
		Load(aVertexSize, aVertexNum, aInitData, GL_STATIC_DRAW);	//委譲
	}
	void Load(u32 aVertexSize, u32 aVertexNum) {
		Load(aVertexSize, aVertexNum, nullptr);	//委譲
	}
	void Load(u32 aVertexSize, u32 aVertexNum, GLenum aUsage) {
		Load(aVertexSize, aVertexNum, nullptr, aUsage);	//委譲
	}


public:
	u32 GetVertexSize() const {
		return mVertexSize;
	}
	u32 GetVertexNum() const {
		return mVertexNum;
	}

private:
	u32 mVertexSize;
	u32 mVertexNum;
};


}

}

}
