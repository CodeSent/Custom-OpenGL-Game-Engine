#pragma once
#include "Shader.h"
#include "Texture.h"

class Material
{
public:
	void setUniforms(Shader& targetShader);
	void disable();
	Texture colorMap;
	Texture NormalMap;
};

