//
//	content	:	OpenGLでのConstantBuffer
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Render/constantBuffer.h"
#include "./Pot/Render/OpenGL/Platform/uniformBufferOpenGLPlatform.h"

namespace cpot {

namespace openGL {

class ConstantBuffer : public ConstantBufferBase {

	#pragma region Load

public:
	void Load(const HashTableKey& aUnionName) CPOT_OR {
		//将来は、名前からデータを検索して、ロードできるようにしたい
	};
	template<typename T>
	BOOL Load(T* aInitData) {
		mUniformBuffer.Load(aInitData);
		return true;
	}

	BOOL Load(void* aInitData, u32 aSize) CPOT_OR {
		mUniformBuffer.Load(aSize, aInitData);
		return true;
	}

	#pragma endregion


	#pragma region Write

public:
	BOOL Write() CPOT_OR {
		return mUniformBuffer.Write();
	}
	BOOL Write(const void* aBuffer) CPOT_OR {
		return mUniformBuffer.Write(aBuffer);
	}

	#pragma endregion


	//取得
	#pragma region Getter

public:
	template<typename T>
	T* GetCPUBuffer() {
		return mUniformBuffer.GetCPUBuffer<T>();
	}

	#pragma endregion


	//設定
	#pragma region Setter

public:
	void SetCPUBuffer(void* aCPUBuffer) CPOT_OR {
		mUniformBuffer.SetCPUBuffer(aCPUBuffer);
	}

	#pragma endregion


public:
	void Release() CPOT_OR {
		mUniformBuffer.Release();
	}

public:
	BOOL IsLoad() const CPOT_OR {
		return mUniformBuffer.IsLoaded();
	}

public:
	platform::UniformBuffer mUniformBuffer;

};

}

using ConstantBuffer = openGL::ConstantBuffer;

}