#pragma once
#ifndef GLFW_PRESENT
#include <GLFW/glfw3.h>
#endif // GLFW_PRESENT
#include <glm.hpp>

#define DF_MAP_KEY_INPUT(W,K) if (glfwGetKey(W,K)  == GLFW_PRESS)   

struct CamMat {
	glm::mat4x4 View;
	glm::mat4x4 Proj;
	glm::vec3 CamPos;
};

using Vector3 = glm::vec3;

class Camera
{
	Vector3 Position = Vector3(0.0f,10.0f,5.0f);
	Vector3 Orientation = Vector3(0.0f,0.0f,-1.0f);
	Vector3 Up = Vector3(0.0f, 1.0f, 0.0f);

	bool FirstClick = true;
public:
	int Width, Height;

	float Speed =  0.05f;
	double Sensitvity =  10.0f;
	float Fov = 90;
	float NearPlane = 0.01f;
	float FarPlane = 1000.0f;

	void Init(int Height, int Width, Vector3 Pos);
	void Matrix(CamMat &Set);
	void Inputs(GLFWwindow* Window);

};