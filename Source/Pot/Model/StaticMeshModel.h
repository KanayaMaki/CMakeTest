#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Render/render.h"
#include "./Pot/Model/Submesh.h"
#include "./Pot/Model/Material.h"

namespace cpot {

struct StaticMesh {
	std::shared_ptr<VertexBuffer> vertex;
	std::shared_ptr<IndexBuffer> index;
};

struct StaticMeshModel {
	StaticMesh mesh;
	u32 submeshNum;
	Submesh<Material> submesh[32];
};

}
