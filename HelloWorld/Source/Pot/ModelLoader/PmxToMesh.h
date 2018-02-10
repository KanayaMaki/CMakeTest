#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/vector.h"

#include "./Pot/ModelLoader/PmxData.h"
#include "./Pot/ModelLoader/ModelCPU.h"

#include "./Pot/Usefull/path.h"


namespace cpot {

class PmxToMesh {

public:
	static void Load(StaticMeshModelCPU& aMesh, const PmxData& aPmx) {
		LoadVertex(aMesh.vertex, aPmx);
		LoadIndex(aMesh.index, aPmx);
		LoadSubMesh(aMesh.submesh, aPmx);
		aMesh.filePath = aPmx.fileName;
	}
	static void LoadVertex(VectorSimple<StaticMeshVertex>& aVertex, const PmxData& aPmx) {

		//���_�f�[�^�̓ǂݍ���
		aVertex.SetSize(aPmx.vertexs.GetSize());
		for (u32 i = 0; i < aPmx.vertexs.GetSize(); i++) {
			aVertex[i].position = Vector3::FromFloat3(aPmx.vertexs[i].location);
			aVertex[i].normal = Vector3::FromFloat3(aPmx.vertexs[i].normal);
			aVertex[i].texCoord = Vector2::FromFloat2(aPmx.vertexs[i].uv);
		}
	}
	static void LoadIndex(VectorSimple<u32>& aIndex, const PmxData& aPmx) {

		//�C���f�b�N�X�f�[�^�̓ǂݍ���
		aIndex.SetSize(aPmx.indexs.GetSize());
		for (u32 i = 0; i < aPmx.indexs.GetSize(); i++) {
			aIndex[i] = aPmx.indexs[i];
		}
	}
	static void LoadSubMesh(VectorSimple<SubMeshCPU<MaterialCPU>>& aSubMesh, const PmxData& aPmx) {

		//�}�e���A���f�[�^�̓ǂݍ���
		aSubMesh.SetSize(aPmx.materials.GetSize());
		for (u32 i = 0; i < aPmx.materials.GetSize(); i++) {

			//�e�N�X�`�����̓ǂݍ���
			s32 lTextureIndex = aPmx.materials[i].textureRef;
			if (lTextureIndex != -1) {
				String<128> lTextureFileName = &(aPmx.textures[lTextureIndex].fileName.buf[0]);
				if (Path::GetEx(lTextureFileName) == "tga") {
					lTextureFileName = Path::ChangeEx(lTextureFileName, "png");
				}
				aSubMesh[i].material.texture.name = lTextureFileName.Get();
			}

			//�g�D�[���e�N�X�`�����̓ǂݍ���
			s32 lToonTextureIndex = aPmx.materials[i].toonTexture;

			//�ėp�g�D�[�����g���ꍇ
			if (aPmx.materials[i].unionToonFlag == 1) {
				if (lToonTextureIndex != -1) {
					aSubMesh[i].material.toonTexture.name = "./toon";
					aSubMesh[i].material.toonTexture.name += ToString::Do(lToonTextureIndex).PaddingLeft('0', 2);
					aSubMesh[i].material.toonTexture.name += ".bmp";
				}
			}
			//�ėp�g�D�[�����g��Ȃ��ꍇ
			else {
				if (lToonTextureIndex != -1) {
					String<128> lToonTextureFileName = &(aPmx.textures[lToonTextureIndex].fileName.buf[0]);
					if (Path::GetEx(lToonTextureFileName) == "tga") {
						lToonTextureFileName = Path::ChangeEx(lToonTextureFileName, "png");
					}
					aSubMesh[i].material.toonTexture.name = lToonTextureFileName.Get();
				}
			}
			


			//�C���f�b�N�X�J�E���g�̓ǂݍ���
			aSubMesh[i].indexCount = aPmx.materials[i].indexNum;

			//�F�Ȃǂ̎擾
			aSubMesh[i].material.diffuse = Color::FromVector4(Vector4::FromFloat4(aPmx.materials[i].diffuse));
			aSubMesh[i].material.ambient = Vector3::FromFloat3(aPmx.materials[i].ambient);
			aSubMesh[i].material.specular = Vector3::FromFloat3(aPmx.materials[i].specular);
			aSubMesh[i].material.specularPower = aPmx.materials[i].specularPow;
		}
	}

	static void Load(SkinMeshModelCPU& aMesh, const PmxData& aPmx) {
		LoadVertex(aMesh.vertex, aPmx);
		LoadIndex(aMesh.index, aPmx);
		LoadSubMesh(aMesh.submesh, aPmx);
		aMesh.filePath = aPmx.fileName;
	}

	static void LoadVertex(VectorSimple<SkinMeshVertex>& aVertex, const PmxData& aPmx) {

		//���_�f�[�^�̓ǂݍ���
		aVertex.SetSize(aPmx.vertexs.GetSize());
		for (u32 i = 0; i < aPmx.vertexs.GetSize(); i++) {
			aVertex[i].position = Vector3::FromFloat3(aPmx.vertexs[i].location);
			aVertex[i].normal = Vector3::FromFloat3(aPmx.vertexs[i].normal);
			aVertex[i].texCoord = Vector2::FromFloat2(aPmx.vertexs[i].uv);
			aVertex[i].weight = Vector3::FromFloat3(aPmx.vertexs[i].weight.weight);
			for (u32 j = 0; j < 4; j++) {
				aVertex[i].weightIndex[j] = aPmx.vertexs[i].weight.index[j];
			}
		}
	}
	
};


}