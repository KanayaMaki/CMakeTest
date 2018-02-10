//
//	content	:	Render‚ÌOpenGL‚Å‚ÌŽÀ‘•
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Usefull/singleton.h"

#include "./Pot/Render/render.h"
#include "./Pot/Render/OpenGL/Platform/renderOpenGLPlatform.h"


namespace cpot {

namespace openGL {

class Render : public RenderBase, public Singleton<Render> {
	friend class Singleton<Render>;

public:
	void SetRasterizer(std::shared_ptr<Rasterizer> aRasterizer) CPOT_OR {
		platform::Render::S().GetCullManager().Set(&(aRasterizer->mCull));
	}
	void SetBlend(std::shared_ptr<Blend> aBlend) CPOT_OR {
		platform::Render::S().GetBlendManager().Set(&(aBlend->mBlend));
	}
	void SetDepthStencil(std::shared_ptr<DepthStencil> aDepthStencil) CPOT_OR {
		platform::Render::S().GetDepthManager().Set(&(aDepthStencil->mDepth));
		platform::Render::S().GetStencilManager().Set(&(aDepthStencil->mStencil));
	}

	void SetViewPort(std::shared_ptr<Viewport> aViewport, u32 aSlotNum) CPOT_OR {
		platform::Render::S().GetViewportManager().Set(&(aViewport->mViewport));
	}

	void SetSampler(std::shared_ptr<Sampler> aSampler, u32 aSlotNum) CPOT_OR {
		platform::Render::S().GetSamplerManager().Set(&(aSampler->mSampler), aSlotNum);
	}

	void SetTexture2D(std::shared_ptr<Texture2D> aTexture, u32 aSlotNum) CPOT_OR {
		platform::Render::S().GetTextureManager().Set(&(aTexture->mTexture), aSlotNum);
	}

	void SetConstantBuffer(std::shared_ptr<ConstantBuffer> aConstantBuffer, u32 aSlotNum) CPOT_OR {
		platform::Render::S().GetUniformBufferManager().Set(&(aConstantBuffer->mUniformBuffer), aSlotNum);
	}


	void SetShader(std::shared_ptr<Shader> aShader) CPOT_OR {
		platform::Render::S().GetInputLayoutManager().SetInputLayout(&(aShader->mInputLayout));
		platform::Render::S().GetProgramManager().Set(&(aShader->mProgram));
	}


	void SetDepthTexture(std::shared_ptr<Texture2D> aDepthTexture) CPOT_OR {
		platform::Render::S().GetRenderTextureManager().SetDepthBuffer(&(aDepthTexture->mDepthBuffer));
	}
	void SetRenderTexture(std::shared_ptr<Texture2D> aRenderTexture, u32 aSlotNum) CPOT_OR {
		if (aRenderTexture) {
			if (aRenderTexture->GetIsBackBuffer()) {
				platform::Render::S().GetRenderTextureManager().SetBackBuffer();
			}
			else {
				platform::Render::S().GetRenderTextureManager().SetTexture(&(aRenderTexture->mTexture), aSlotNum);
			}
		}
		
	}

	void SetIndexBuffer(std::shared_ptr<IndexBuffer> aIndexBuffer) CPOT_OR {
		platform::Render::S().GetElementArrayBufferManager().Set(&(aIndexBuffer->mElementArrayBuffer));
	}
	void SetVertexBuffer(std::shared_ptr<VertexBuffer> aVertexBuffer) CPOT_OR {
		platform::Render::S().GetArrayBufferManager().Set(&(aVertexBuffer->mArrayBuffer));
	}


	void SetToDevice() CPOT_OR {
		platform::Render::S().SetToDevice();
	}


	void DrawIndexed(u32 aIndexCount, u32 aStartIndexLocation) CPOT_OR {
		platform::Render::S().DrawElement(aIndexCount, aStartIndexLocation);
	}
	void Draw(u32 aVertexCount, u32 aStartVertexLocation) CPOT_OR {
		//platform::Render::S().Draw(aVertexCount, aStartVertexLocation);
	}

	void Present() CPOT_OR {
		platform::Render::S().SwapBuffer();
	}
};

}

using Render = openGL::Render;

}