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


glBindBufferBase(GL_UNIFORM_BUFFER, aBindNum, GetGLNum());

*/



class UniformBuffer : public Buffer {

	//ロード
	#pragma region Load

public:
	void Load(GLsizei aSize, void* aInitData, GLenum aUsage) {
		mCPUBuffer = aInitData;
		aSize = Align<u32>(aSize, 256UL);
		Buffer::Load(GL_UNIFORM_BUFFER, aSize, aInitData, aUsage);
	}
	void Load(GLsizei aSize, void* aInitData) {
		Load(aSize, aInitData, GL_DYNAMIC_DRAW);	//委譲
	}
	void Load(GLsizei aSize) {
		Load(aSize, nullptr);	//委譲
	}
	void Load(GLsizei aSize, GLenum aUsage) {
		Load(aSize, nullptr, aUsage);	//委譲
	}
	template<typename T>
	void Load(T* aInitData) {
		Load(sizeof(T), aInitData);	//委譲
	}

	#pragma endregion


	//書き込み
	#pragma region Write

public:
	BOOL Write() {
		return Buffer::Write(mCPUBuffer, GetSize());
	}
	BOOL Write(const void* aBuffer) {
		return Buffer::Write(aBuffer, GetSize());
	}

	#pragma endregion


public:
	void Bind(u32 aBindIndex) {
		glBindBufferBase(GL_UNIFORM_BUFFER, aBindIndex, GetGLNum());
	}


public:
	template<typename T>
	T* GetCPUBuffer() {
		return (T*)(mCPUBuffer);
	}
	void SetCPUBuffer(void* aCPUBuffer) {
		mCPUBuffer = aCPUBuffer;
	}


public:
	void Reset() {
		mCPUBuffer = nullptr;
		Buffer::Reset();
	}


private:
	void* mCPUBuffer;

};


}

}

}
