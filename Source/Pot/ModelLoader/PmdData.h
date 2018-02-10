#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/vector.h"

namespace cpot {

struct PmdData {

	#pragma pack(push,1)	//アラインメント制御をオフる
	//ヘッダー
	struct Header {
		u8 magic[3];
		f32 version;
		u8 model_name[20];
		u8 comment[256];
	} header;

	//頂点リスト
	struct Vertex {
		f32 pos[3];
		f32 normal_vec[3];
		f32 uv[2];
		u16 bone_num[2];
		u8 bone_weight;
		u8 edgeFlag;
	};
	VectorSimple<Vertex> vertexs;

	//インデックスのリスト
	VectorSimple<u16> indexs;

	//マテリアルのリスト
	struct Material {
		f32 diffuse[3];
		f32 alpha;
		f32 specular;
		f32 specularColor[3];
		f32 ambientColor[3];
		u8 toonIndex;
		u8 edgeFlag;
		u32 faceVertexCount;
		CHAR textureFileName[20];
	};
	VectorSimple<Material> materials;

	//ボーンのリスト
	struct Bone {
		CHAR boneName[20];
		u16 parentBoneIndex;
		u16 tailPosBoneIndex;
		u8 boneType;
		u16 ikParentBoneIndex;
		f32 boneHeadPos[3];
	};
	VectorSimple<Bone> bones;

	#pragma pack(pop)	//アラインメント制御エンド
};

}
