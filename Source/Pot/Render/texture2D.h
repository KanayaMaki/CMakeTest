//
//	content	:	Textureのインターフェース
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/namedResource.h"

namespace cpot {

class Texture2DBase : public NamedResource {

public:
	enum CFormat {
		cR8Uint,
		cRGBA8Uint,
		cR32Float,
		cRGBA32Float,
	};


public:
	CPOT_VI void Load(const HashTableKey& aUnionName) CPOT_ZR;
	CPOT_VI void Load(u32 aWidth, u32 aHeight, CFormat aFormat, BOOL aIsRenderTarget, BOOL aIsShaderResource) CPOT_ZR;
	CPOT_VI void Load(u32 aWidth, u32 aHeight, CFormat aFormat, BOOL aIsRenderTarget, BOOL aIsShaderResource, BOOL aIsDepthStencil) CPOT_ZR;
	CPOT_VI void LoadFileName(const CHAR* aFileName) CPOT_ZR;

public:
	CPOT_VI void Release() CPOT_ZR;

public:
	CPOT_VI void ClearDepth(f32 aDepth) CPOT_ZR;
	CPOT_VI void ClearColor(const Color& aColor) CPOT_ZR;

public:
	CPOT_VI u32 GetWidth() CPOT_ZR;
	CPOT_VI u32 GetHeight() CPOT_ZR;

public:
	CPOT_VI BOOL IsLoad() const CPOT_ZR;

};

}




#ifdef CPOT_ON_DIRECTX11
#include "./Pot/Render/DirectX11/texture2DDirectX11.h"
#elif defined CPOT_ON_OPENGL
#include "./Pot/Render//OpenGL/texture2DOpenGL.h"
#endif