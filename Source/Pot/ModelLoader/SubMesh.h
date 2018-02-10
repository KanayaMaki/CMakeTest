#pragma once

#include "./Pot/Atom/atom.h"
#include "./Pot/List/vector.h"

namespace cpot {

template <typename MaterialType>
struct SubMeshCPU {
	u32 indexCount;
	MaterialType material;
};


}
