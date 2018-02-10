#pragma once

#include "./Pot/Render/OpenGL/Platform/deviceOpenGLPlatform.h"


namespace cpot {

namespace openGL {

namespace platform {


struct InputLayoutElement {
	u32 mBufferIndex;
	GLuint mCount;
	GLenum mType;
	GLboolean mNormal;
	GLuint mStride;
	GLuint mOffset;
};
inline InputLayoutElement CreateInputLayoutElement(u32 aBufferIndex, GLenum aType, GLuint aCount, GLuint aStride, GLuint aOffset) {
	return InputLayoutElement{ aBufferIndex, aCount, aType, GL_FALSE, aStride, aOffset };
}


class InputLayout {
public:
	void Load(const InputLayoutElement* aLayout, u32 aLayoutCount) {
		for (u32 i = 0; i < aLayoutCount; i++) {
			mLayout[i] = aLayout[i];
		}
		mLayoutCount = aLayoutCount;
	}
	InputLayoutElement& GetInputLayoutElement(u32 aLayoutIndex) {
		return mLayout[aLayoutIndex];
	}


public:
	u32 GetLayoutCount() const {
		return mLayoutCount;
	}

private:
	InputLayoutElement mLayout[16];
	u32 mLayoutCount;
};


}

}

}
