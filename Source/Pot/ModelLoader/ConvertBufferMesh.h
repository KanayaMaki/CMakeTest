#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/vector.h"

#include "./Pot/Usefull/buffer.h"

#include "./Pot/ModelLoader/ModelCPU.h"

#include "./Pot/Usefull/path.h"


namespace cpot {

class BufferToMesh {

public:
	template<typename VertexType, typename MaterialType>
	static void Load(ModelCPU<VertexType, MaterialType>& aMesh, Buffer& aData, PathString& aFilePath) {
		LoadVertex(aMesh.vertex, aData);
		LoadIndex(aMesh.index, aData);
		LoadSubMesh(aMesh.submesh, aData);
		aMesh.filePath = aFilePath;
	}

	template<typename VertexType, typename MaterialType>
	static void Load(ModelCPU<VertexType, MaterialType>& aMesh, PathString& aFilePath) {
		FileIn lFile;
		lFile.Open(aFilePath.Get(), true);

		Buffer lData;
		lFile.Read(lData);

		Load(aMesh, lData, aFilePath);
	}


private:
	template <typename VertexType>
	static void LoadVertex(VectorSimple<VertexType>& aVertex, Buffer& aData) {

		//頂点フォーマットの確認
		u32 lVertexType = aData.Read<u32>();
		if (lVertexType != VertexType::cVertexType) return;

		//頂点データの読み込み
		u32 lVertexNum = aData.Read<u32>();
		aVertex.SetSize(lVertexNum);

		u32 lVertexSize = sizeof(VertexType);

		aData.Read(&aVertex[0], lVertexSize * lVertexNum);
	}

	static void LoadIndex(VectorSimple<u32>& aIndex, Buffer& aData) {

		//インデックスフォーマットの確認
		u32 lIndexType = aData.Read<u32>();

		//頂点データの読み込み
		u32 lIndexNum = aData.Read<u32>();
		aIndex.SetSize(lIndexNum);

		u32 lIndexSize = sizeof(u32);
		u32* lIndexData = (u32*)(&(aData[aData.GetPosition()]));

		aData.Read(&aIndex[0], lIndexSize * lIndexNum);
	}


	static void LoadMaterial(MaterialCPU& aMaterial, Buffer& aData) {

		//テクスチャ名の読み込み
		u32 lTextureNameLen = aData.Read<u32>();
		aData.Read(&(aMaterial.texture.name), lTextureNameLen);

		u32 lToonTextureNameLen = aData.Read<u32>();
		aData.Read(&(aMaterial.toonTexture.name), lToonTextureNameLen);


		//色などの取得
		aMaterial.diffuse = aData.Read<Color>();
		aMaterial.ambient = aData.Read<Vector3>();
		aMaterial.specular = aData.Read<Vector3>();
		aMaterial.specularPower = aData.Read<f32>();
	}
	static void LoadMaterial(BampMaterialCPU& aMaterial, Buffer& aData) {

		//テクスチャ名の読み込み
		u32 lTextureNameLen = aData.Read<u32>();
		aData.Read(&(aMaterial.texture.name), lTextureNameLen);

		u32 lBampTextureNameLen = aData.Read<u32>();
		aData.Read(&(aMaterial.bampTexture.name), lBampTextureNameLen);


		//色などの取得
		aMaterial.diffuse = aData.Read<Color>();
		aMaterial.ambient = aData.Read<Vector3>();
		aMaterial.specular = aData.Read<Vector3>();
		aMaterial.specularPower = aData.Read<f32>();
	}

	template <typename MaterialType>
	static void LoadSubMesh(VectorSimple<SubMeshCPU<MaterialType>>& aSubMesh, Buffer& aData) {

		//頂点データの読み込み
		u32 lSubMeshNum = aData.Read<u32>();
		aSubMesh.SetSize(lSubMeshNum);

		//マテリアルデータの読み込み
		for (u32 i = 0; i < lSubMeshNum; i++) {

			//インデックスカウントの読み込み
			aSubMesh[i].indexCount = aData.Read<u32>();
			
			//マテリアルの読み込み
			LoadMaterial(aSubMesh[i].material, aData);
		}
	}


public:
	template<typename VertexType, typename MaterialType>
	static void Save(const ModelCPU<VertexType, MaterialType>& aMesh, Buffer& aData) {
		aData.Release();
		SaveVertex(aMesh.vertex, aData);
		SaveIndex(aMesh.index, aData);
		SaveSubMesh(aMesh.submesh, aData);
	}
	
private:
	template <typename VertexType>
	static void SaveVertex(const VectorSimple<VertexType>& aVertex, Buffer& aData) {

		//頂点フォーマットの書き込み
		u32 lVertexFormat = VertexType::cVertexType;
		aData.Add(&lVertexFormat);

		//インデックスデータの書き込み
		u32 lVertexNum = aVertex.GetSize();
		aData.Add(&lVertexNum);

		aData.Add((const BYTE*)(&aVertex[0]), lVertexNum * sizeof(VertexType));
	}

	static void SaveIndex(const VectorSimple<u32>& aIndex, Buffer& aData) {

		//インデックスフォーマットの書き込み
		u32 lIndexSize = 4;
		aData.Add(&lIndexSize);

		//インデックスデータの書き込み
		u32 lIndexNum = aIndex.GetSize();
		aData.Add(&lIndexNum);

		aData.Add((const BYTE*)(&aIndex[0]), lIndexNum * lIndexSize);

	}

	static void SaveMaterial(const MaterialCPU& aMaterial, Buffer& aData) {

		//テクスチャ名の書き込み
		u32 lTextureNameLen = aMaterial.texture.name.GetLength() + 1;	//終端文字も書き込む
		aData.Add(&lTextureNameLen);

		aData.Add((const BYTE*)(aMaterial.texture.name.Get()), lTextureNameLen);


		//トゥーンテクスチャ名の書き込み
		u32 lToonTextureNameLen = aMaterial.toonTexture.name.GetLength() + 1;
		aData.Add(&lToonTextureNameLen);

		aData.Add((const BYTE*)(aMaterial.toonTexture.name.Get()), lToonTextureNameLen);


		//色などの書き込み
		aData.Add(&aMaterial.diffuse);
		aData.Add(&aMaterial.ambient);
		aData.Add(&aMaterial.specular);
		aData.Add(&aMaterial.specularPower);
	}
	static void SaveMaterial(const BampMaterialCPU& aMaterial, Buffer& aData) {

		//テクスチャ名の書き込み
		u32 lTextureNameLen = aMaterial.texture.name.GetLength() + 1;	//終端文字も書き込む
		aData.Add(&lTextureNameLen);

		aData.Add((const BYTE*)(aMaterial.texture.name.Get()), lTextureNameLen);


		//ノーマルテクスチャ名の書き込み
		u32 lNormalTextureNameLen = aMaterial.bampTexture.name.GetLength() + 1;
		aData.Add(&lNormalTextureNameLen);

		aData.Add((const BYTE*)(aMaterial.bampTexture.name.Get()), lNormalTextureNameLen);


		//色などの書き込み
		aData.Add(&aMaterial.diffuse);
		aData.Add(&aMaterial.ambient);
		aData.Add(&aMaterial.specular);
		aData.Add(&aMaterial.specularPower);
	}

	template <typename MaterialType>
	static void SaveSubMesh(const VectorSimple<SubMeshCPU<MaterialType>>& aSubMesh, Buffer& aData) {

		//サブメッシュデータの書き込み
		u32 lSubMeshNum = aSubMesh.GetSize();
		aData.Add(&lSubMeshNum);

		for (u32 i = 0; i < lSubMeshNum; i++) {

			//インデックスカウントの書き込み
			aData.Add(&aSubMesh[i].indexCount);

			//マテリアルの書き込み
			SaveMaterial(aSubMesh[i].material, aData);
		}
	}

};


}
