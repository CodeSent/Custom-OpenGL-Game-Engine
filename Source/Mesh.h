#pragma once
#include <vector>
#include <unordered_map>
#include "Types.h"
#include "ModelLoader/Loader.h"

#include "VertexArray.h"
#include "Buffers.h"

#include "Coord.h"
#include "Camera.h"
#include "Shader.h"
#include "Material.h"
#include "Light.h"



struct MeshData {
	size_t VBO, VAO;
	VertexArray vArray;
	Buffer vBuffer;
	objLoader mainData;
	size_t Indecies;
	bool Created;
};

class staticMesh
{
	MeshData *Data;
	static void buildModel(MeshData& Data, std::string filePath);
	Shader  objShader;
	void setUniforms();
	static VertexPointer Atributes[];
	static std::unordered_map<std::string, MeshData> MeshStorage;
public:
	static Light Sun;
	float lightInfluence = 1.0f;
	Material objMaterial;
	static CamMat CameraMatrix;
	static std::string ShaderFile;
	Geomerty3D Transformation;
	void Load(std::string filePath);
	void Draw();
	void Delete();
	static void DeleteAll();
	static void preLoadModel(std::string filePath);
	static void preLoadModel(std::vector<std::string> filePaths);
};

