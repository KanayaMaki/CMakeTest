#version 450 core

vec4 mul(vec4 v, mat4x4 m) {
	return v * m;
}


layout(location = 0) in vec3 InPosLoc;
layout(location = 1) in vec3 InNorLoc;
layout(location = 2) in vec2 InTexCoord;

layout(location = 0) out vec3 OutPosWor;
layout(location = 1) out vec3 OutNorWor;
layout(location = 2) out vec2 OutTexCoord;

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
	float _Dummy0;
	vec3 CameraPosition;
	float _Dummy1;
	vec3 ToLight;
	float _Dummy3;
	vec3 CameraPositionLoc;
	float _Dummy4;
};

void main() {
	vec4 lPosWor = mul(vec4(InPosLoc, 1), World);
	OutPosWor = lPosWor.xyz / lPosWor.w;

	vec4 lPosView = mul(lPosWor, View);
	vec4 lPosProj = mul(lPosView, Proj);
	gl_Position =  lPosProj;

	vec4 lNorWor = mul(vec4(InNorLoc, 1), NorWorld);
	OutNorWor = lNorWor.xyz / lNorWor.w;

	OutTexCoord = InTexCoord;
}
