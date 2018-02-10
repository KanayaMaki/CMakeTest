#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Render/render.h"
#include "./Pot/Model/Submesh.h"

namespace cpot {

struct BampMaterial {
	std::shared_ptr<Texture2D> texture;
	std::shared_ptr<Texture2D> bampTexture;
	Color diffuse;
	Vector3 specular;
	f32 specularPower;
	Vector3 ambient;
};

struct StaticTangentMesh {
	std::shared_ptr<VertexBuffer> vertex;
	std::shared_ptr<IndexBuffer> index;
};

struct StaticTangentMeshModel {
	StaticTangentMesh mesh;
	u32 submeshNum;
	Submesh<BampMaterial> submesh[32];
};

}
