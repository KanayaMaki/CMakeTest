#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Usefull/buffer.h"


namespace cpot {

struct BitmapData {
	s32 width;
	s32 height;
	s32 depth;
	s32 pixelBytes;
	Buffer data;
};

}
