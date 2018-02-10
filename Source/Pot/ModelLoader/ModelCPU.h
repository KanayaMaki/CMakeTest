#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/vector.h"

#include "./Pot/ModelLoader/SubMesh.h"
#include "./Pot/ModelLoader/Material.h"

namespace cpot {


template <typename VertexType, typename MaterialType>
struct ModelCPU {
public:
	VectorSimple<VertexType> vertex;
	VectorSimple<u32> index;
	VectorSimple<SubMeshCPU<MaterialType>> submesh;
	PathString filePath;

public:
	void LoadVertex(VectorSimple<VertexType>& lVertex) {
		lVertex.SetSize(vertex.GetSize());
		for (u32 i = 0; i < vertex.GetSize(); i++) {
			lVertex[i] = vertex[i];
		}
	}

	void Scale(const Vector3 aScale) {
		for (u32 i = 0; i < vertex.GetSize(); i++) {
			vertex[i].position *= aScale;
		}
	}
};

struct StaticMeshVertex {
	enum {
		cVertexType = 0
	};
	Vector3 position;
	Vector3 normal;
	TexCoord texCoord;
};

struct SkinMeshVertex {
	enum {
		cVertexType = 1
	};
	Vector3 position;
	Vector3 normal;
	TexCoord texCoord;
	Vector3 weight;
	u16 weightIndex[4];
};

struct StaticTangentMeshVertex {
	enum {
		cVertexType = 2
	};
	Vector3 position;
	Vector3 normal;
	Vector3 tangent;
	Vector3 biNormal;
	TexCoord texCoord;
};

using SkinMeshModelCPU = ModelCPU<SkinMeshVertex, MaterialCPU>;
using StaticMeshModelCPU = ModelCPU<StaticMeshVertex, MaterialCPU>;
using StaticTangentMeshModelCPU = ModelCPU<StaticTangentMeshVertex, BampMaterialCPU>;

}
