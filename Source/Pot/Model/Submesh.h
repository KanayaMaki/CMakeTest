#pragma once

#include "./Pot/Atom/atom.h"

namespace cpot {

template <typename MaterialType>
struct Submesh {
	u32 indexCount;
	u32 indexStartCount;
	MaterialType material;
};

}
