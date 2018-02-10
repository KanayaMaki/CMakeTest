//
//	content	:	コンポーネント
//	author	:	SaitoYoshiki
//

#pragma once

#include "./Pot/Game/component.h"

namespace cpot {

class Renderer : public Component {
	CPOT_TYPE(Renderer, Component)

public:
	Renderer();
	~Renderer() override;


	//呼び出される関数
	#pragma region Event
public:
	//描画処理
	virtual void OnStart() {}

	//描画処理
	virtual void OnRender() {}

	#pragma endregion


	//優先度
	#pragma region Priority
public:
	virtual s32 GetPriority() {
		return 0;
	}

	#pragma endregion

};

class RendererManager : public Singleton<RendererManager> {

	friend class Renderer;

	//登録&解除。Updaterが呼び出す
	#pragma region Regist&Remove

private:
	void Regist(Renderer* aRenderer) {
		mRendererNowFrame.PushBack(aRenderer);
	}
	void Remove(Renderer* aRenderer) {
		mRendererNowFrame.Remove(aRenderer);
		mRenderer.Remove(aRenderer);
	}

public:
	void Clear() {
		mRenderer.Clear();
		mRendererNowFrame.Clear();
	}

	#pragma endregion


public:
	void Update() {
		Merge();	//前のフレームに追加されたレンダラを統合する
		Sort();	//優先度順に並び替える
	}

	void Render() {
		RenderRenderer();	//レンダラを描画する
	}

private:
	void Merge() {
		for (u32 i = 0; i < mRendererNowFrame.GetSize(); i++) {
			mRendererNowFrame[i]->OnStart();
		}

		//統合
		while(mRendererNowFrame.GetSize() != 0) {
			mRenderer.PushBack(mRendererNowFrame.PopBack());
		}
	}

	void Sort() {
		//優先度によってソートする。
		//本当ならstd::sortでラムダ式を渡してソートしたいが、マルチプラットフォームの為std空間を直接触れないので、自分でバブルソートを実装
		//mRenderer.Sort();

		//降順にソート
		for (u32 i = 0; i < mRenderer.GetSize(); i++) {
			for (u32 j = 0; j < mRenderer.GetSize() - 1; j++) {
				//奥に大きいのがあれば
				if (mRenderer[j]->GetPriority() < mRenderer[j + 1]->GetPriority()) {
					//交換して、大きいのが手前に来るように
					auto tmp = mRenderer[j];
					mRenderer[j] = mRenderer[j + 1];
					mRenderer[j + 1] = tmp;
				}
			}
		}
	}

	void RenderRenderer() {
		for (u32 i = 0; i < mRenderer.GetSize(); i++) {
			mRenderer[i]->OnRender();
		}
	}


private:
	Vector<Renderer*> mRendererNowFrame;	//新しく追加されたレンダラー
	Vector<Renderer*> mRenderer;
};



struct WVPBuffer {
	ShaderMatrix4x4 mWorld;
	ShaderMatrix4x4 mView;
	ShaderMatrix4x4 mProjection;
	ShaderMatrix4x4 mNormalWorld;
};
struct MaterialBuffer {
	Color mDiffuse;
};
struct OtherBuffer {
	Vector3 mLightDirection;
	f32 mDummy0;
	Vector3 mCameraPosition;
	f32 mDummy1;
	Vector3 mToLight;
	f32 mDummy3;
	Vector3 mCameraPositionLoc;
	f32 mDummy4;
};
struct ToonLineBuffer {
	f32 mLineWidth;
	f32 mDummy0[3];
};


}