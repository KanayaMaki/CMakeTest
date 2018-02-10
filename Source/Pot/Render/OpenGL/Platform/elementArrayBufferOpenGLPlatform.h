#pragma once

#include "./Pot/Render/OpenGL/Platform/bufferOpenGLPlatform.h"


//


namespace cpot {

namespace openGL {

namespace platform {

class ElementArrayBuffer : public Buffer {

	//ロード
	#pragma region Load

public:
	void Load(GLenum aType, u32 aNum, const void* aInitData, GLenum aMode, GLenum aUsage) {
		mIndexNum = aNum;
		mType = aType;
		mMode = aMode;
		Buffer::Load(GL_ELEMENT_ARRAY_BUFFER, GetTypeSize(aType) * aNum, aInitData, aUsage);
	}
	void Load(GLenum aType, u32 aNum, const void* aInitData, GLenum aMode) {
		Load(aType, aNum, aInitData, aMode, GL_STATIC_DRAW);	//委譲
	}
	void Load(GLenum aType, u32 aNum, GLenum aMode) {
		Load(aType, aNum, nullptr, aMode);	//委譲
	}

	void Load(GLenum aType, u32 aNum, GLenum aMode, GLenum aUsage) {
		Load(aType, aNum, nullptr, aMode, aUsage);	//委譲
	}

	#pragma endregion


	//取得
	#pragma region Getter

public:
	GLenum GetType() const {
		return mType;
	}
	u32 GetIndexNum() const {
		return mIndexNum;
	}
	u32 GetIndexSize() const {
		return GetTypeSize(mType);
	}
	GLenum GetMode() const {
		return mMode;
	}

	#pragma endregion


public:
	void SetToDevice() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GetGLNum());
	}


private:
	static u32 GetTypeSize(GLenum aType) {
		switch (aType) {
			case GL_UNSIGNED_BYTE:
			case GL_BYTE:
				return 1;
			case GL_UNSIGNED_SHORT:
			case GL_SHORT:
				return 2;
			case GL_UNSIGNED_INT:
			case GL_INT:
			case GL_FLOAT:
				return 4;
		}
		return 0;
	}


	//フィールド
	#pragma region Field

private:
	GLenum mMode;
	GLenum mType;
	u32 mIndexNum;

	#pragma endregion


};


}

}

}
