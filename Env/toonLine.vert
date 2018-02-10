#version 450 core

vec4 mul(vec4 v, mat4x4 m) {
	return v * m;
}


layout(location = 0) in vec3 InPosLoc;
layout(location = 1) in vec3 InNorLoc;
layout(location = 2) in vec2 InTexCoord;

layout(binding = 0, column_major) uniform Data {
    mat4x4  World;
	mat4x4  View;
	mat4x4  Proj;
	mat4x4  NorWorld;
};
layout(binding = 1) uniform Material {
    vec4 Diffuse;
};
layout(binding = 2) uniform Other {
	vec3 LightDirection;
	float _Other_Dummy0;
	vec3 CameraPosition;
	float _Dummy1;
	vec3 ToLight;
	float _Dummy3;
	vec3 CameraPositionLoc;
	float _Dummy4;
};
layout(binding = 3) uniform Toon {
    float LineWidth;
	vec3 _Toon_Dummy0;
};

void main() {

	vec3 lPosLocExtend = InPosLoc + normalize(InNorLoc) * LineWidth;

	vec4 lPosWor = mul(vec4(lPosLocExtend, 1), World);
	vec4 lPosView = mul(lPosWor, View);
	vec4 lPosProj = mul(lPosView, Proj);

	gl_Position =  lPosProj;
}
