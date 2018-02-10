//
//	content	:	スプライトを描画するレンダラー
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Game/renderer.h"
#include "./Pot/Render/constantBuffer.h"
#include "./Pot/ModelLoader/ModelCPU.h"
#include "./Pot/Config/config.h"

#include "./Pot/Render/render.h"

namespace cpot {


//
//	スプライトを張り付けられるクラス
//
class SpriteMesh {
public:
	void Load() {
		LoadVertexBuffer();
		LoadIndexBuffer();
	}

	void WriteVertexBuffer() {

		//プロジェクション座標での頂点位置に変換
		Quad2D lProjQuad = quad * (Vector2::One() / Config::S().GetScreenSize()) * Vector2().XY(2.0f) - Vector2().XY(1.0f);
		const f32 lProjZLoc = 0.0f;

		//書き込むデータの作成
		StaticMeshVertex lVertex[]{
			{ Vector3().XY(lProjQuad.GetPoint(Quad2D::cLeftBottom)).Z(lProjZLoc),{ 0.0f, 0.0f, -1.0f },{ 0.0f, 1.0f } },
			{ Vector3().XY(lProjQuad.GetPoint(Quad2D::cLeftTop)).Z(lProjZLoc),{ 0.0f, 0.0f, -1.0f },{ 0.0f, 0.0f } },
			{ Vector3().XY(lProjQuad.GetPoint(Quad2D::cRightBottom)).Z(lProjZLoc),{ 0.0f, 0.0f, -1.0f },{ 1.0f, 1.0f } },
			{ Vector3().XY(lProjQuad.GetPoint(Quad2D::cRightTop)).Z(lProjZLoc),{ 0.0f, 0.0f, -1.0f },{ 1.0f, 0.0f } },
		};
		//書き込み
		vertexBuffer->Write(lVertex);
	}

private:
	void LoadVertexBuffer() {
		//頂点座標の初期化
		quad.SetRect(Vector2::Zero(), Config::S().GetScreenSize());

		vertexBuffer = std::make_shared<VertexBuffer>();
		vertexBuffer->Load(sizeof(StaticMeshVertex), 4, nullptr, true);
		WriteVertexBuffer();
	}
	void LoadIndexBuffer() {
		u16 lIndex[]{ 0, 1, 2, 2, 1, 3 };

		indexBuffer = std::make_shared<IndexBuffer>();
		indexBuffer->Load(IndexBuffer::cU16, 6, IndexBuffer::cTriangleList, lIndex);
	}

public:
	std::shared_ptr<VertexBuffer> vertexBuffer;
	std::shared_ptr<IndexBuffer> indexBuffer;

	Quad2D quad;
};




class SpriteRenderer : public Renderer {
	CPOT_TYPE(SpriteRenderer, Renderer)

public:
	SpriteRenderer() {
		priority = -10;
		sprite.Load();
	}

	//呼び出される関数
	#pragma region Event
public:
	//描画処理
	virtual void OnStart() {
		//外から変更できないプロパティ
		sampler = ResourceList<Sampler>::S().Find("Diffuse");
		shader = ResourceList<Shader>::S().Find("Sprite");
		rasterizer = ResourceList<Rasterizer>::S().Find("CullCCW");
		depthStencil = ResourceList<DepthStencil>::S().Find("NoTest");

		//外から変更できるプロパティ。すでに初期化されている可能性がある
		if (blend == nullptr) {
			blend = ResourceList<Blend>::S().Find("Normal");
		}
		if (renderTarget == nullptr) {
			//renderTarget = ResourceList<Texture2D>::S().Find("RenderTarget");
			renderTarget = ResourceList<Texture2D>::S().Find("BackBuffer");
		}
		if (renderTargetDepth == nullptr) {
			//renderTargetDepth = ResourceList<Texture2D>::S().Find("RenderTargetDepth");
			renderTargetDepth = ResourceList<Texture2D>::S().Find("BackBufferDepth");
		}
	}

	//描画処理
	virtual void OnRender() {

		//テクスチャが設定されていない時
		if (texture == nullptr) return;

		//事前に取得しておく
		auto wvpBuffer = ResourceList<ConstantBuffer>::S().Find("WVP");
		auto materialBuffer = ResourceList<ConstantBuffer>::S().Find("Material");
		auto otherBuffer = ResourceList<ConstantBuffer>::S().Find("Other");
		auto toonLineBuffer = ResourceList<ConstantBuffer>::S().Find("ToonLine");


		wvpBuffer->GetCPUBuffer<WVPBuffer>()->mWorld = Matrix4x4::Unit() * Matrix4x4::FromScale(Vector3::One() * 2.0f);
		wvpBuffer->GetCPUBuffer<WVPBuffer>()->mNormalWorld = Matrix4x4::Unit();
		wvpBuffer->GetCPUBuffer<WVPBuffer>()->mView = Matrix4x4::Unit();
		wvpBuffer->GetCPUBuffer<WVPBuffer>()->mProjection = Matrix4x4::Unit();
		wvpBuffer->Write();

		materialBuffer->GetCPUBuffer<MaterialBuffer>()->mDiffuse = Color::White();
		materialBuffer->Write();

		//スプライトのデータの上書き
		sprite.WriteVertexBuffer();

		Render::S().SetBlend(blend);
		Render::S().SetRasterizer(rasterizer);
		Render::S().SetDepthStencil(depthStencil);
		Render::S().SetVertexBuffer(sprite.vertexBuffer);
		Render::S().SetIndexBuffer(sprite.indexBuffer);
		Render::S().SetDepthTexture(renderTargetDepth);
		Render::S().SetConstantBuffer(wvpBuffer, 0);
		Render::S().SetConstantBuffer(materialBuffer, 1);
		Render::S().SetRenderTexture(renderTarget, 0);
		Render::S().SetShader(shader);

		Render::S().SetSampler(sampler, 0);
		Render::S().SetTexture2D(texture, 0);
		Render::S().SetToDevice();
		Render::S().DrawIndexed(6, 0);
	}

	#pragma endregion


	//優先度
	#pragma region Priority
public:
	virtual s32 GetPriority() {
		return priority;
	}

	#pragma endregion


public:
	s32 priority;
	SpriteMesh sprite;
	std::shared_ptr<Blend> blend;
	std::shared_ptr<Texture2D> renderTarget;
	std::shared_ptr<Texture2D> renderTargetDepth;

	std::shared_ptr<Texture2D> texture;

private:
	std::shared_ptr<Sampler> sampler;
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Rasterizer> rasterizer;
	std::shared_ptr<DepthStencil> depthStencil;
};

}
