//
//	content	:	OpenGL‚Å‚ÌVertexBuffer
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Render/vertexBuffer.h"
#include "./Pot/Render/OpenGL/Platform/arrayBufferOpenGLPlatform.h"

namespace cpot {

namespace openGL {

class VertexBuffer : public VertexBufferBase {

	#pragma region Load

public:
	BOOL Load(u32 aVertexSize, u32 aVertexNum, const void* aInitData, BOOL aCPUWritable) CPOT_OR {
		mArrayBuffer.Load(aVertexSize, aVertexNum, aInitData, aCPUWritable ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
		return true;
	}
	BOOL Load(u32 aVertexSize, u32 aVertexNum, const void* aInitData) CPOT_OR {
		mArrayBuffer.Load(aVertexSize, aVertexNum, aInitData);
		return true;
	}
	

	#pragma endregion


	#pragma region Write

public:
	BOOL Write(const void* aData) CPOT_OR {
		return mArrayBuffer.Write(aData);
	}
	BOOL Write(const void* aData, u32 aSize) CPOT_OR {
		return mArrayBuffer.Write(aData, aSize);
	}

	#pragma endregion


	//Žæ“¾
	#pragma region Getter

public:
	u32 GetVertexSize() const CPOT_OR {
		return mArrayBuffer.GetVertexSize();
	}
	u32 GetVertexNum() const CPOT_OR {
		return mArrayBuffer.GetVertexNum();
	}

	#pragma endregion


public:
	void Release() CPOT_OR {
		mArrayBuffer.Release();
	}

public:
	BOOL IsLoad() const CPOT_OR {
		return mArrayBuffer.IsLoaded();
	}

public:
	platform::ArrayBuffer mArrayBuffer;

};

}

using VertexBuffer = openGL::VertexBuffer;

}