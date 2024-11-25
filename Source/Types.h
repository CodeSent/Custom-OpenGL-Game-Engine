#pragma once

struct vec2 {
	float x, y;
};
struct vec3 {
	float x, y, z;
};

struct vertexData {
	vec3 Position;
	vec3 Normal;
	vec2 UV;
};

struct VertexPointer {
	unsigned short Index;
	unsigned short Length;
	unsigned int Type;
	unsigned int Stride;
	unsigned int Pointer;
};