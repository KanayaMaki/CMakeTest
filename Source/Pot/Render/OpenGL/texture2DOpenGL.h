//
//	content	:	TextureのOpenGLでの実装
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Usefull/resourceLoadList.h"
#include "./Pot/Render/texture2D.h"
#include "./Pot/Render/OpenGL/Platform/textureOpenGLPlatform.h"
#include "./Pot/Render/OpenGL/Platform/depthBufferOpenGLPlatform.h"
#include "./Pot/Render/OpenGL/Platform/renderOpenGLPlatform.h"



namespace cpot {

namespace openGL {


class Texture2DData : public ResourceLoadList<Texture2DData, String<128>> {

};

class Texture2D : public Texture2DBase {

public:
	Texture2D() {
		aIsBackBuffer = false;
	}

public:
	struct GLFormat {
		GLenum format;
		GLenum type;
	};

	static GLFormat Convert(CFormat aFormat) {

		GLFormat lRes;
		switch (aFormat) {
			case cR8Uint:
				lRes.format = GL_RED;
				lRes.type = GL_UNSIGNED_BYTE;
				break;
			case cRGBA8Uint:
				lRes.format = GL_RGBA;
				lRes.type = GL_UNSIGNED_BYTE;
				break;
			case cR32Float:
				lRes.format = GL_RED;
				lRes.type = GL_FLOAT;
				break;
			case cRGBA32Float:
				lRes.format = GL_RGBA;
				lRes.type = GL_FLOAT;
				break;
			default:
				lRes.format = GL_INVALID_ENUM;
				lRes.type = GL_INVALID_ENUM;
				break;
		}
		return lRes;
	}

public:
	void Load(const HashTableKey& aUnionName) CPOT_OR {
		mTexture.Load(Texture2DData::S().Get(aUnionName).Get());
	};
	void Load(u32 aWidth, u32 aHeight, CFormat aFormat, BOOL aIsRenderTarget, BOOL aIsShaderResource) CPOT_OR {
		Load(aWidth, aHeight, aFormat, aIsRenderTarget, aIsShaderResource, false);
	}
	void Load(u32 aWidth, u32 aHeight, CFormat aFormat, BOOL aIsRenderTarget, BOOL aIsShaderResource, BOOL aIsDepthStencil) CPOT_OR {
		if (!aIsDepthStencil) {
			mTexture.Load(aWidth, aHeight, Convert(aFormat).format, Convert(aFormat).type);
		}
		else {
			mDepthBuffer.Load(aWidth, aHeight);
		}
	}
	void LoadFileName(const CHAR* aFileName) CPOT_OR {
		mTexture.Load(aFileName);
	};
	void LoadPlatform() {
		aIsBackBuffer = true;
	};

public:
	void Release() CPOT_OR {
		mTexture.Release();
		mDepthBuffer.Release();
	};

	void ClearDepth(f32 aDepth) CPOT_OR {
		if (aIsBackBuffer) {
			platform::Render::S().GetRenderTextureManager().ClearBackBuffer(aDepth);
		}
		else if (mDepthBuffer.IsLoaded()) {
			platform::Render::S().GetRenderTextureManager().ClearDepth(&mDepthBuffer, aDepth);
		}
	}
	void ClearColor(const Color& aColor) CPOT_OR {
		if (aIsBackBuffer) {
			platform::Render::S().GetRenderTextureManager().ClearBackBuffer(aColor);
		}
		else if (mTexture.IsLoaded()) {
			platform::Render::S().GetRenderTextureManager().ClearColor(&mTexture, aColor);
		}
	}

public:
	BOOL IsLoad() const CPOT_OR {
		return mTexture.IsLoaded();
	};

public:
	u32 GetWidth() CPOT_OR {
		return mTexture.GetWidth();
	}
	u32 GetHeight() CPOT_OR {
		return mTexture.GetHeight();
	}

	BOOL GetIsBackBuffer() {
		return aIsBackBuffer;
	}

	//フィールド
	#pragma region Field

public:
	platform::Texture2D mTexture;
	platform::DepthBuffer mDepthBuffer;
	BOOL aIsBackBuffer;

	#pragma endregion
};

}

using Texture2D = openGL::Texture2D;

}