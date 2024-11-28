#pragma once
#include "RenderOBJ.h"

#include "Coord.h"
#include "Camera.h"
#include "Types.h"
#include "Light.h"
#include "Material.h"

#include <vector>
#include <string>


class Object
{
private:
protected:
	std::vector <vertexData>* Vpoint;
	std::vector<unsigned int>* Ipoint;
	std::vector<VertexPointer> * PointerData;
	RenderOBJ Main;
	Shader  objShader;
	virtual void setUniforms();
	virtual void postRender();
	bool Created = false;
	bool Geometry = false;
public:
	Texture Tex;
	std::string ShaderFile = "Shaders/2D/ShaderV3";
	static CamMat CameraMatrix;
	Geomerty3D Transformation;
	void Process();
	void Draw();
	void Delete();
};



class Pyramid : public Object {
	std::vector <vertexData> V = {
		{{-0.5f, 0.0f, 0.5f}, {0.0f, 0.0f, 0.0f},  {0.0f, 0.0f}},
		{{-0.5f, 0.0f,-0.5f}, {0.0f, 0.0f, 0.0f},  {5.0f, 0.0f}},
		{{ 0.5f, 0.0f,-0.5f}, {0.0f, 0.0f, 0.0f},  {0.0f, 0.0f}},
		{{ 0.5f, 0.0f, 0.5f}, {0.0f, 0.0f, 0.0f},  {5.0f, 0.0f}},
		{{ 0.0f, 0.8f, 0.0f}, {0.0f, 0.0f, 0.0f},  {2.5f, 5.0f}}
	};
	std::vector<unsigned int> I = {
		0,1,2,
		0,2,3,

		4,1,0,
		4,2,1,
		4,3,2,
		4,0,3
	};
	std::vector<VertexPointer> PointData = {
		{0, 3, GL_FLOAT, sizeof(vertexData), 0},
		{1, 3, GL_FLOAT, sizeof(vertexData), 3 * sizeof(float)},
		{2, 2, GL_FLOAT, sizeof(vertexData), 6 * sizeof(float)}
	};
protected:
	static RenderOBJ Main;
	static bool Created;
	void setUniforms();
public:
	Pyramid();
};

class Plane : public Object {
	std::vector <vertexData> V = {
		{{-0.5f, 0.0f,-0.5f}, {0.0f, 1.0f, 0.0f},  {  0.0f,   0.0f}},
		{{-0.5f, 0.0f, 0.5f}, {0.0f, 1.0f, 0.0f},  {  0.0f, 100.0f}},
		{{ 0.5f, 0.0f,-0.5f}, {0.0f, 1.0f, 0.0f},  {100.0f,   0.0f}},
		{{ 0.5f, 0.0f, 0.5f}, {0.0f, 1.0f, 0.0f},  {100.0f, 100.0f}}
	//-0.5f, 0.0f,-0.5f,    0.0f,   0.0f,
	//-0.5f, 0.0f, 0.5f,    0.0f, 100.0f,
	// 0.5f, 0.0f,-0.5f,  100.0f,   0.0f,
	// 0.5f, 0.0f, 0.5f,  100.0f, 100.0f
	};
	std::vector<unsigned int> I = {
		0,1,3,
		3,2,0
	};
	std::vector<VertexPointer> PointData = {
		{0, 3, GL_FLOAT, sizeof(vertexData), 0},
		{1, 3, GL_FLOAT, sizeof(vertexData), 3 * sizeof(float)},
		{2, 2, GL_FLOAT, sizeof(vertexData), 6 * sizeof(float)}
	};
protected:
	static RenderOBJ Main;
	static bool Created;
	void setUniforms();
	void postRender();
public:
	Material objMaterial;

	Plane();
};