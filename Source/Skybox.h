#pragma once
#include "Shader.h"
#include "Camera.h"

struct SkyboxIds {
	unsigned int Vbo, Vao, ibo, Cubemap;
};

class Skybox
{
public:
	std::string skyboxTextureFolder = "Textures/Skybox1";
	Skybox() {};
	Skybox(const char* Folder);
	void render();
	void Delete();
	static CamMat cam;
private:
	bool Complied = false;
	SkyboxIds dataIds;
	Shader skyboxShader;
	void loadSkyboxTexture();
	void process();
	void Bind(bool Enable);
};

