//
//	content	:	OpenGL‚Å‚ÌIndexBuffer
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Render/indexBuffer.h"
#include "./Pot/Render/OpenGL/Platform/elementArrayBufferOpenGLPlatform.h"

namespace cpot {

namespace openGL {

class IndexBuffer : public IndexBufferBase {

	#pragma region Load

public:
	BOOL Load(CType aIndexType, u32 aIndexNum, CTopology aTopology, const void* aInitData) CPOT_OR {
		mElementArrayBuffer.Load(ConvertType(aIndexType), aIndexNum, aInitData, ConvertTopology(aTopology));
		return true;
	}

	#pragma endregion


	//Žæ“¾
	#pragma region Getter

public:
	CType GetIndexType() const CPOT_OR {
		return ConvertType(mElementArrayBuffer.GetType());
	}
	u32 GetIndexNum() const CPOT_OR {
		return mElementArrayBuffer.GetIndexNum();
	}
	CTopology GetTopology() const CPOT_OR {
		return ConvertTopology(mElementArrayBuffer.GetMode());
	}

	#pragma endregion


public:
	void Release() CPOT_OR {
		mElementArrayBuffer.Release();
	}

public:
	BOOL IsLoad() const CPOT_OR {
		return mElementArrayBuffer.IsLoaded();
	}


	#pragma region Convert

public:
	static CType ConvertType(GLenum aIndexType) {
		switch (aIndexType) {
			case GL_UNSIGNED_BYTE:
				return cU8;
			case GL_UNSIGNED_SHORT:
				return cU16;
			case GL_UNSIGNED_INT:
				return cU32;
		}
		return cInvalidType;
	}
	static GLenum ConvertType(CType aIndexType) {
		switch (aIndexType) {
			case cU8:
				return GL_UNSIGNED_BYTE;
			case cU16:
				return GL_UNSIGNED_SHORT;
			case cU32:
				return GL_UNSIGNED_INT;
		}
		return GL_INVALID_ENUM;
	}

	static CTopology ConvertTopology(GLenum aTopology) {
		switch (aTopology) {
			case GL_TRIANGLES:
				return cTriangleList;
			case GL_TRIANGLE_STRIP:
				return cTriangleStrip;
		}
		return cInvalidTopology;
	}
	static GLenum ConvertTopology(CTopology aTopology) {
		switch (aTopology) {
			case cTriangleList:
				return GL_TRIANGLES;
			case cTriangleStrip:
				return GL_TRIANGLE_STRIP;
		}
		return GL_INVALID_ENUM;
	}

	#pragma endregion


public:
	platform::ElementArrayBuffer mElementArrayBuffer;

};

}

using IndexBuffer = openGL::IndexBuffer;

}