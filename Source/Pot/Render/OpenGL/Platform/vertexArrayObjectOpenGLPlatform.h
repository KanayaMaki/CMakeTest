#pragma once

#include "./Pot/Render/OpenGL/Platform/bufferOpenGLPlatform.h"
#include "./Pot/Render/OpenGL/Platform/arrayBufferOpenGLPlatform.h"


namespace cpot {

namespace openGL {

namespace platform {


struct ArrayBufferLayout {
	GLuint mBufferNum;
	GLuint mCount;
	GLenum mType;
	GLboolean mNormal;
	GLuint mStride;
	GLuint mOffset;
};

inline ArrayBufferLayout CreateArrayBufferLayout(const ArrayBuffer& aArrayBuffer, GLuint aCount, GLenum aType, GLuint aOffset) {
	ArrayBufferLayout res = { aArrayBuffer.GetGLNum(), aCount, aType, GL_FALSE,  (GLuint)aArrayBuffer.GetVertexSize(), aOffset };
	return res;
}


class VertexArrayObject {
public:
	void Load(const ArrayBufferLayout* aLayout, u32 aLayoutCount) {

		//Create VertexArrayObject
		glGenVertexArrays(1, &mGLNum);
		glBindVertexArray(mGLNum);	//Bind

		//Set Vertex Data To VertexArrayObject
		for (u32 i = 0; i < aLayoutCount; i++) {

			glEnableVertexAttribArray(i);
			glBindBuffer(GL_ARRAY_BUFFER, aLayout[i].mBufferNum);
			glVertexAttribPointer(i, aLayout[i].mCount, aLayout[i].mType,
				aLayout[i].mNormal, aLayout[i].mStride, (void*)(aLayout[i].mOffset));
		}
		mLayoutCount = aLayoutCount;

		glBindVertexArray(0);	//Disable
	}

	void Release() {
		if (!IsLoaded()) {
			return;	//読み込まれていないなら、処理をしない
		}

		glDeleteVertexArrays(1, &mGLNum);
	}

	void SetToDevice() {
		glBindVertexArray(mGLNum);	//Bind
	}


public:
	BOOL IsLoaded() const {
		return mGLNum != 0;
	}

	GLuint GetGLNum() const {
		return mGLNum;
	}
	u32 GetLayoutCount() const {
		return mLayoutCount;
	}

private:
	GLuint mGLNum;
	u32 mLayoutCount;
};


}

}

}
