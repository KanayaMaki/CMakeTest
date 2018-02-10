#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/Render/OpenGL/Platform/deviceOpenGLPlatform.h"

#include "./Pot/Render/OpenGL/Platform/blendOpenGLPlatform.h"
#include "./Pot/Render/OpenGL/Platform/cullOpenGLPlatform.h"
#include "./Pot/Render/OpenGL/Platform/depthOpenGLPlatform.h"
#include "./Pot/Render/OpenGL/Platform/stencilOpenGLPlatform.h"
#include "./Pot/Render/OpenGL/Platform/elementArrayBufferOpenGLPlatform.h"
#include "./Pot/Render/OpenGL/Platform/arrayBufferOpenGLPlatform.h"
#include "./Pot/Render/OpenGL/Platform/uniformBufferOpenGLPlatform.h"
#include "./Pot/Render/OpenGL/Platform/frameBufferOpenGLPlatform.h"
#include "./Pot/Render/OpenGL/Platform/samplerOpenGLPlatform.h"
#include "./Pot/Render/OpenGL/Platform/stencilOpenGLPlatform.h"
#include "./Pot/Render/OpenGL/Platform/textureOpenGLPlatform.h"
#include "./Pot/Render/OpenGL/Platform/shaderOpenGLPlatform.h"
#include "./Pot/Render/OpenGL/Platform/vertexArrayObjectOpenGLPlatform.h"
#include "./Pot/Render/OpenGL/Platform/depthBufferOpenGLPlatform.h"
#include "./Pot/Render/OpenGL/Platform/inputLayoutOpenGLPlatform.h"
#include "./Pot/Render/OpenGL/Platform/viewportOpenGLPlatform.h"


namespace cpot {

namespace openGL {

namespace platform {



template <typename ElementType, u32 cSlotMax>
class ElementManager {
public:
	ElementManager() {
		Reset();
	}

protected:
	void Reset() {
		for (s32 i = 0; i < cSlotMax; i++) {
			mElement[i] = nullptr;
			mChanged[i] = false;
		}
	}

public:
	void Clear() {
		Reset();
		SetChanged();
	}

public:
	void Set(ElementType* aElement, u32 aSlotNum) {
		CPOT_ASSERT(aSlotNum < cSlotMax);
		if (mElement[aSlotNum] == aElement) {
			return;
		}
		mElement[aSlotNum] = aElement;
		SetChanged(aSlotNum);
	}

	ElementType* Get() const {
		return mElement[0];
	}
	ElementType* Get(u32 aSlotNum) const {
		CPOT_ASSERT(aSlotNum < cSlotMax);
		return mElement[aSlotNum];
	}

	BOOL IsChanged(u32 aSlotNum) const {
		return mChanged[aSlotNum];
	}
	void SetChanged(u32 aSlotNum) {
		mChanged[aSlotNum] = true;
	}
	void SetChanged() {
		for (u32 i = 0; i < cSlotMax; i++) {
			mChanged[i] = true;
		}
	}
	void SetNotChanged(u32 aSlotNum) {
		mChanged[aSlotNum] = false;
	}
	u32 SlotMaxNum() {
		return cSlotMax;
	}

protected:
	ElementType* mElement[cSlotMax];
	BOOL mChanged[cSlotMax];
};


#pragma region BlendManager

class BlendManager : public ElementManager<Blend, 1> {
	using super = ElementManager<Blend, 1>;

public:
	BlendManager() {
		Reset();
	}

	void Set(Blend* aElement) {
		if (mElement[0] != aElement) {
			mElement[0] = aElement;
			SetChanged(0);
		}
	}

	void SetToDevice() {
		if (IsChanged(0)) {
			if (mElement[0]) {
				mElement[0]->SetToDevice();
			}
			else {
				mNull.SetToDevice();
			}
			SetNotChanged(0);
		}
	}

private:
	Blend mNull;
};

#pragma endregion


#pragma region CullManager

class CullManager : public ElementManager<Cull, 1> {
	using super = ElementManager<Cull, 1>;

public:
	CullManager() {
		Reset();
	}


	void Set(Cull* aElement) {
		if (mElement[0] != aElement) {
			mElement[0] = aElement;
			SetChanged(0);
		}
	}

	void SetToDevice() {
		if (IsChanged(0)) {
			if (mElement[0]) {
				mElement[0]->SetToDevice();
			}
			else {
				mNull.SetToDevice();
			}
			SetNotChanged(0);
		}
	}

private:
	Cull mNull;
};

#pragma endregion


#pragma region DepthManager

class DepthManager : public ElementManager<Depth, 1> {
	using super = ElementManager<Depth, 1>;

public:
	DepthManager() {
		Reset();
	}

	void Set(Depth* aElement) {
		if (mElement[0] != aElement) {
			mElement[0] = aElement;
			SetChanged(0);
		}
	}

	void SetToDevice() {
		if (IsChanged(0)) {
			if (mElement[0]) {
				mElement[0]->SetToDevice();
			}
			else {
				mNull.SetToDevice();
			}
			SetNotChanged(0);
		}
	}

private:
	Depth mNull;
};

#pragma endregion



#pragma region StencilManager

class StencilManager : public ElementManager<Stencil, 1> {
	using super = ElementManager<Stencil, 1>;

public:
	StencilManager() {
		Reset();
	}

	void Set(Stencil* aElement) {
		if (mElement[0] != aElement) {
			mElement[0] = aElement;
			SetChanged(0);
		}
	}

	void SetToDevice() {
		if (IsChanged(0)) {
			if (mElement[0]) {
				mElement[0]->SetToDevice();
			}
			else {
				mNull.SetToDevice();
			}
			SetNotChanged(0);
		}
	}

private:
	Stencil mNull;
};

#pragma endregion




#pragma region VertexArrayObjectManager

class VertexArrayObjectManager : public ElementManager<VertexArrayObject, 1> {
	using super = ElementManager<VertexArrayObject, 1>;

public:
	VertexArrayObjectManager() {
		Reset();
	}

	void Set(VertexArrayObject* aElement) {
		if (mElement[0] != aElement) {
			mElement[0] = aElement;
			SetChanged(0);
		}
	}

	void SetToDevice() {
		if (IsChanged(0)) {
			if (mElement[0]) {
				mElement[0]->SetToDevice();
			}
			else {
				mNull.SetToDevice();
			}
			SetNotChanged(0);
		}
	}

private:
	VertexArrayObject mNull;
};

#pragma endregion


#pragma region ArrayBufferManager

class ArrayBufferManager : public ElementManager<ArrayBuffer, 1> {
	using super = ElementManager<ArrayBuffer, 1>;

public:
	ArrayBufferManager() {
		Reset();
	}

	void Set(ArrayBuffer* aElement) {
		if (mElement[0] != aElement) {
			mElement[0] = aElement;
			SetChanged(0);
		}
	}
};

#pragma endregion


#pragma region ElementArrayBufferManager

class ElementArrayBufferManager : public ElementManager<ElementArrayBuffer, 1> {
	using super = ElementManager<ElementArrayBuffer, 1>;

public:
	ElementArrayBufferManager() {
		Reset();
	}

	void Set(ElementArrayBuffer* aElement) {
		if (mElement[0] != aElement) {
			mElement[0] = aElement;
			SetChanged(0);
		}
	}

	void SetToDevice() {
		if (IsChanged(0)) {
			if (mElement[0]) {
				mElement[0]->SetToDevice();
			}
			else {
				mNull.SetToDevice();
			}
			SetNotChanged(0);
		}
	}

private:
	ElementArrayBuffer mNull;
};

#pragma endregion



#pragma region TextureManager

constexpr u32 cTextureMaxNum = 8;


#pragma region SamplerManager

class SamplerManager : public ElementManager<Sampler, cTextureMaxNum> {
	using super = ElementManager<Sampler, cTextureMaxNum>;

public:
	SamplerManager() {
		Reset();
	}
};

#pragma endregion


class TextureManager : public ElementManager<Texture, cTextureMaxNum> {
	using super = ElementManager<Texture, cTextureMaxNum>;

public:
	TextureManager() {
		Reset();
	}

	void SetToDevice(SamplerManager& aSampler) {

		static const GLenum lGLTexture[]{
			GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, GL_TEXTURE3, GL_TEXTURE4, GL_TEXTURE5, GL_TEXTURE6, GL_TEXTURE7,
			GL_TEXTURE8, GL_TEXTURE9, GL_TEXTURE10, GL_TEXTURE11, GL_TEXTURE12, GL_TEXTURE13, GL_TEXTURE14, GL_TEXTURE15,
		};

		for (u32 i = 0; i < SlotMaxNum(); i++) {

			BOOL lSamplerChange = aSampler.IsChanged(i);
			BOOL lTextureChange = IsChanged(i);

			if (lSamplerChange || lTextureChange) {

				glActiveTexture(lGLTexture[i]);

				if (lTextureChange) {
					if (mElement[i]) {
						mElement[i]->Bind();
					}
					else {
						mNullTexture.Bind();
					}
					SetNotChanged(i);
				}
				
				if (lSamplerChange) {
					if (aSampler.Get(i)) {
						aSampler.Get(i)->Bind(i);
					}
					else {
						mNullSampler.Bind(i);
					}
					aSampler.SetNotChanged(i);
				}
			}
		}
	}

private:
	Sampler mNullSampler;
	Texture2D mNullTexture;
};

#pragma endregion



#pragma region UniformBufferManager

constexpr u32 cUniformBufferMaxNum = 8;

class UniformBufferManager : public ElementManager<UniformBuffer, cUniformBufferMaxNum> {
	using super = ElementManager<UniformBuffer, cUniformBufferMaxNum>;

public:
	UniformBufferManager() {
		Reset();
	}

	void SetToDevice(Program* aProgram) {
		for (u32 i = 0; i < SlotMaxNum(); i++) {
			if (IsChanged(i)) {

				glUniformBlockBinding(aProgram->GetGLNum(), i, i);
				if (mElement[i]) {
					mElement[i]->Bind(i);
				}
				else {
					mNull.Bind(i);
				}

				SetNotChanged(i);
			}
		}
	}

private:
	UniformBuffer mNull;
};

#pragma endregion



#pragma region ProgramManager

class ProgramManager : public ElementManager<Program, 1> {
	using super = ElementManager<Program, 1>;

public:
	ProgramManager() {
		Reset();
	}

	void Set(Program* aElement) {
		if (mElement[0] != aElement) {
			mElement[0] = aElement;
			SetChanged(0);
		}
	}

	void SetToDevice(UniformBufferManager& aUniformBufferManager) {
		if (IsChanged(0)) {
			if (mElement[0]) {
				mElement[0]->Use();
			}
			else {
				mNull.Use();
			}
			aUniformBufferManager.SetChanged();
			aUniformBufferManager.SetToDevice(mElement[0]);
			SetNotChanged(0);
		}
	}

private:
	Program mNull;
};

#pragma endregion



#pragma region RenderTextureManager

class RenderTextureManager {
public:
	RenderTextureManager() {
		mFrameBuffer.Load();
		mIsSetBackBuffer = true;	//最初はバックバッファーがセットされた状態に
	}

public:
	Texture* GetTexture(u32 aIndex) const {
		return mTexture[aIndex];
	}
	void SetTexture(Texture* aTexture, u32 aIndex) {
		CPOT_ASSERT(aIndex <= 8);
		mTexture[aIndex] = aTexture;
		UnSetBackBuffer();
	}

	DepthBuffer* GetDepthBuffer() const {
		return mDepthBuffer;
	}
	void SetDepthBuffer(DepthBuffer* aDepthBuffer) {
		mDepthBuffer = aDepthBuffer;
	}

	void SetBackBuffer() {
		mIsSetBackBuffer = true;
	}
	void UnSetBackBuffer() {
		mIsSetBackBuffer = false;
	}
	BOOL IsSetBackBuffer() const {
		return mIsSetBackBuffer;
	}

	void SetToDevice() {

		//バックバッファがセットされている場合
		if (mIsSetBackBuffer) {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);	//フレームバッファを外す
		}
		//セットされていない場合
		else {
			u32 lMaxSlot = 0;
			for (u32 i = 0; i < 8; i++) {
				GLuint lTex = 0;
				if (mTexture[i]) {
					lTex = mTexture[i]->GetGLNum();
					lMaxSlot = i + 1;
				}
				mFrameBuffer.AttachmentColor(lTex, i);
			}
			GLuint lDepth = 0;
			if (mDepthBuffer) lDepth = mDepthBuffer->Num();
			mFrameBuffer.AttachmentDepth(lDepth);
			mFrameBuffer.SetDrawBuffer(lMaxSlot);
		}
	}

	void ClearColor(GLuint aNum, const Color& c) {
		for (u32 i = 0; i < 8; i++) {
			mFrameBuffer.AttachmentColor(0, i);
		}
		mFrameBuffer.AttachmentColor(aNum, 0);
		mFrameBuffer.SetDrawBuffer(1);
		glClearColor(c.r, c.g, c.b, c.a);
		glClear(GL_COLOR_BUFFER_BIT);
		mFrameBuffer.AttachmentColor(0, 0);
	}
	void ClearDepth(GLuint aNum, f32 aDepth) {
		mFrameBuffer.AttachmentDepth(aNum);
		mFrameBuffer.SetDrawBuffer(1);
		glClearDepthf(aDepth);
		glClear(GL_DEPTH_BUFFER_BIT);
		mFrameBuffer.AttachmentDepth(0);
	}
	void ClearColor(Texture* aTexture, const Color& c) {
		ClearColor(aTexture->GetGLNum(), c);
	}
	void ClearDepth(DepthBuffer* aDepthBuffer, f32 aDepth) {
		ClearDepth(aDepthBuffer->Num(), aDepth);
	}

	void ClearBackBuffer(const Color& c) {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(c.r, c.g, c.b, c.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void ClearBackBuffer(f32 aDepth) {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearDepthf(aDepth);
		glClear(GL_DEPTH_BUFFER_BIT);
	}

private:
	Texture* mTexture[8];
	DepthBuffer* mDepthBuffer;

	FrameBuffer mFrameBuffer;
	BOOL mIsSetBackBuffer;
};

#pragma endregion



#pragma region InputLayoutManager

class InputLayoutManager {
public:
	InputLayoutManager() {
		mInputLayout = nullptr;
	}

public:
	void SetInputLayout(InputLayout* aInputLayout)  {
		mInputLayout = aInputLayout;
	}


	void SetToDevice(ArrayBufferManager& aArrayBufferManager) {
		if (mInputLayout == nullptr) {
			return;
		}

		for (u32 i = 0; i < mInputLayout->GetLayoutCount(); i++) {
			InputLayoutElement& lLayout = mInputLayout->GetInputLayoutElement(i);

			glEnableVertexAttribArray(i);
			glBindBuffer(GL_ARRAY_BUFFER, aArrayBufferManager.Get(lLayout.mBufferIndex)->GetGLNum());
			glVertexAttribPointer(i, lLayout.mCount, lLayout.mType,
				lLayout.mNormal, lLayout.mStride, (void*)(lLayout.mOffset));
		}
	}

private:
	InputLayout* mInputLayout;
};

#pragma endregion



#pragma region ViewportManager

class ViewportManager {
public:
	ViewportManager() {
		mViewport = nullptr;
	}

public:
	void Set(Viewport* aViewport) {
		mViewport = aViewport;
	}


	void SetToDevice() {
		if (mViewport == nullptr) {
			return;
		}

		mViewport->SetToDevice();
	}

private:
	Viewport* mViewport;
};

#pragma endregion





}

}

}
