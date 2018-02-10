#version 450 core

layout(location = 0) out vec4 OutColor;

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

	vec4 color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	color *= Diffuse;
	
	OutColor = color;
}
