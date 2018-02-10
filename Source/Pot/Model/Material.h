#pragma once

#include "./Pot/Atom/atom.h"

#include "./Pot/Render/texture2D.h"

namespace cpot {

struct Material {
	std::shared_ptr<Texture2D> texture;
	std::shared_ptr<Texture2D> toonTexture;
	Color diffuse;
	Vector3 specular;
	f32 specularPower;
	Vector3 ambient;
};

}
