#version 450 core

vec4 mul(vec4 v, mat4x4 m) {
	return v * m;
}


layout(location = 0) in vec3 InPosLoc;
layout(location = 1) in vec3 InNorLoc;
layout(location = 2) in vec2 InTexCoord;

layout(location = 0) out vec2 OutTexCoord;

layout(binding = 0, column_major) uniform Data {
	mat4x4  World;
	mat4x4  View;
	mat4x4  Proj;
	mat4x4  NorWorld;
};
layout(binding = 1) uniform Material {
	vec4 Diffuse;
};

void main() {
	//vec4 lPosWor = mul(vec4(InPosLoc, 1), World);
	//vec4 lPosView = mul(lPosWor, View);
	//vec4 lPosProj = mul(lPosView, Proj);
	gl_Position =  vec4(InPosLoc, 1);

	OutTexCoord = InTexCoord;
}
