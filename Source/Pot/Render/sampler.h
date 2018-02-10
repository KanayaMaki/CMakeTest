//
//	content	:	Samplerのインターフェース
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/namedResource.h"

namespace cpot {

class SamplerBase : public NamedResource {
public:
	enum CUVMode {
		cWrap,
		cClamp,
	};

public:
	CPOT_VI void Load(const HashTableKey& aUnionName) CPOT_ZR;
	CPOT_VI void Load(CUVMode aMode) CPOT_ZR;

public:
	CPOT_VI void Release() CPOT_ZR;

public:
	CPOT_VI BOOL IsLoad() const CPOT_ZR;
};

}

#ifdef CPOT_ON_DIRECTX11
#include "./Pot/Render/DirectX11/samplerDirectX11.h"
#elif defined CPOT_ON_OPENGL
#include "./Pot/Render/OpenGL/samplerOpenGL.h"
#endif