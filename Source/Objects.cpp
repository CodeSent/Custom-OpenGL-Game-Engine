#include <GL/glew.h>
#include "Objects.h"
#include "iostream"





CamMat Object::CameraMatrix;

void Object::setUniforms()
{
	
}

void Object::postRender()
{

}

void Object::Process()
{
	if (Vpoint == nullptr or Ipoint == nullptr or PointerData == nullptr) return;
	objShader.Build(ShaderFile, Geometry);
	Main.Build(&((*Vpoint)[0].Position.x), Vpoint->size() * 8, &(*Ipoint)[0], Ipoint->size(),
		(*PointerData)
	);
	/*
	{
		{0, 3, GL_FLOAT, 5 * sizeof(float), 0},
		{1, 2, GL_FLOAT, 5 * sizeof(float), 3 * sizeof(float)}
	}
	*/
	Created = true;
}

void Object::Draw()
{
	if (!Created) Process();
	Main.beginDraw();
	objShader.Bind(true);
	Tex.Bind(true);
	setUniforms();
	Main.Push();
	Tex.Bind(false);
	objShader.Bind(false);
	postRender();

}

void Object::Delete()
{
	Main.Delete();
}



void Pyramid::setUniforms()
{
	glm::mat4 ModelMat = glm::mat4(1.0f);
	glm::mat4 ViewMat = glm::mat4(1.0f);
	glm::mat4 ProjMat = glm::mat4(1.0f);

	//ViewMat = glm::translate(ViewMat, glm::vec3(0.0f, -0.5f, -2.0f));
	//ProjMat = glm::perspective(glm::radians(70.0f), (float)(500 / 500), 0.1f, 100.0f);

	ModelMat = Transformation.getModelMatrix();

	ViewMat = CameraMatrix.View;
	ProjMat = CameraMatrix.Proj;

	objShader.setUnifrom("u_Model", ModelMat);
	objShader.setUnifrom("u_View", ViewMat);
	objShader.setUnifrom("u_Proj", ProjMat);

	objShader.setUniform("Tex0", 0);
}

Pyramid::Pyramid()
{
	Vpoint = &V;
	Ipoint = &I;
	PointerData = &PointData;
	ShaderFile = "Shaders/3D/ShaderV1";
}

void Plane::setUniforms()
{
	glm::mat4 ModelMat = glm::mat4(1.0f);
	glm::mat4 ViewMat = glm::mat4(1.0f);
	glm::mat4 ProjMat = glm::mat4(1.0f);

	ModelMat = Transformation.getModelMatrix();

	ViewMat = CameraMatrix.View;
	ProjMat = CameraMatrix.Proj;

	objShader.setUnifrom("u_Model", ModelMat);
	objShader.setUnifrom("u_View", ViewMat);
	objShader.setUnifrom("u_Proj", ProjMat);

	//Sun.setUnifroms(objShader);

	gameLighting::setUnifroms(objShader);

	objShader.setUniform("camPos", CameraMatrix.CamPos);
	objShader.setUniform("lightInfluence", 1.0f);

	objMaterial.setUniforms(objShader);
}

void Plane::postRender()
{
	objMaterial.disable();
}

Plane::Plane()
{
	Vpoint = &V;
	Ipoint = &I;
	PointerData = &PointData;
	ShaderFile = "Shaders/3D/ShaderV2";
	Geometry = true;

}
