#pragma once
#include <glm.hpp>
#include "unordered_map"
#include "Shader.h"

struct Light
{
	static glm::vec3 SunDir;
	glm::vec3 Color = {1.0f,1.0f,1.0f}, Pos = { 7.5f,15.0f,10.0f };
	float Am = 0.1f , Diff = 0.8f, Spec = 1.0f;
	void setUnifroms(Shader& objShader);
	static void setSunUnifroms(Shader& objShader);
};

enum lightType {
	POINT,
	SPOT
};

struct lightObject {
	lightType Type = POINT;
	glm::vec3 Dir = {0.0f,-1.0f,0.0f};
	glm::vec3 Color = { 1.0f,1.0f,1.0f }, Pos = { 7.5f,15.0f,10.0f };
	float Am = 0.1f, Diff = 0.8f, Spec = 1.0f;
	float Quadratic = 0.0f, Linear = 0.0f, Constant = 0.5f;
	bool Enabled = true;
};

class gameLighting {
	static std::unordered_map<size_t, lightObject> LightsInScene;
	static size_t totalLights;
	static void setSunUnifroms(Shader& objShader);
public:
	static glm::vec3 SunDir;
	static lightObject* createLightSource();
	static lightObject* createLightSource(glm::vec3 Pos);
	static lightObject* createLightSource(glm::vec3 Pos, glm::vec3 Color);

	static lightObject* createLightSource(lightType Type);
	static lightObject* createLightSource(glm::vec3 Pos, lightType Type);
	static lightObject* createLightSource(glm::vec3 Pos, glm::vec3 Color, lightType Type);
	static void setUnifroms(Shader& objShader);
};