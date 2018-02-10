#version 450 core

vec4 mul(vec4 v, mat4x4 m) {
	return v * m;
}
vec3 mul(vec3 aVector, mat4x4 aMatrix) {
	vec4 lVector = mul(vec4(aVector, 1.0f), aMatrix);
	return lVector.xyz / lVector.w;
}


layout(location = 0) in vec3 InPosLoc;
layout(location = 1) in vec3 InNorLoc;
layout(location = 2) in vec3 InTanLoc;
layout(location = 3) in vec3 InBiNorLoc;
layout(location = 4) in vec2 InTexCoord;

layout(location = 0) out vec3 OutPosWor;
layout(location = 1) out vec3 OutToLightTan;
layout(location = 2) out vec3 OutToCameraTan;
layout(location = 3) out vec2 OutTexCoord;


vec3 TransformToTangentSpace(vec3 aVec, vec3 aNormal, vec3 aTangent, vec3 aBiNormal) {

	mat4x4 lTanToLoc = mat4x4(
		vec4(aTangent.x, aTangent.y, aTangent.z, 0.0f),
		vec4(aBiNormal.x, aBiNormal.y, aBiNormal.z, 0.0f),
		vec4(aNormal.x, aNormal.y, aNormal.z, 0.0f),
		vec4(0.0f, 0.0f, 0.0f, 1.0f)
		);
	lTanToLoc = transpose(lTanToLoc);
	mat4x4 lLocToTan = transpose(lTanToLoc);

	vec3 lVecTan = mul(aVec, lLocToTan);

	return lVecTan;
}


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

	OutToLightTan = TransformToTangentSpace(normalize(ToLight), InNorLoc, InTanLoc, InBiNorLoc);

	vec3 lToCamera = CameraPositionLoc - InPosLoc;
	OutToCameraTan = TransformToTangentSpace(normalize(lToCamera), InNorLoc, InTanLoc, InBiNorLoc);
	
	OutTexCoord = InTexCoord;
}
