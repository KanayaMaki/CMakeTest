//
//	content	:	IndexBufferのインターフェース
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/namedResource.h"

namespace cpot {

class IndexBufferBase : public NamedResource {

	//列挙子
	#pragma region Enum

public:
	enum CType {
		cU8,
		cU16,
		cU32,
		cInvalidType
	};
	enum CTopology {
		cTriangleList,
		cTriangleStrip,
		cInvalidTopology
	};

	#pragma endregion


public:
	CPOT_VI ~IndexBufferBase() {}

	#pragma region Load

public:
	CPOT_VI BOOL Load(CType aIndexType, u32 aIndexNum, CTopology aTopology, const void* aInitData) CPOT_ZR;

	#pragma endregion



	//取得
	#pragma region Getter

public:
	CPOT_VI CType GetIndexType() const CPOT_ZR;
	CPOT_VI u32 GetIndexNum() const CPOT_ZR;
	CPOT_VI CTopology GetTopology() const CPOT_ZR;

	#pragma endregion


public:
	CPOT_VI void Release() CPOT_ZR;

public:
	CPOT_VI BOOL IsLoad() const CPOT_ZR;

};

}


#ifdef CPOT_ON_DIRECTX11
#include "./Pot/Render/DirectX11/indexBufferDirectX11.h"
#elif defined CPOT_ON_OPENGL
#include "./Pot/Render/OpenGL/indexBufferOpenGL.h"
#endif