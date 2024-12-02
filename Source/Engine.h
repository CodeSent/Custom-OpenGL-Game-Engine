#pragma once
#include "RenderOBJ.h"
#include "Skybox.h"
#include "Camera.h"
#include <GLFW\glfw3.h>

enum keyCode {
	NULL_KEY = -1,

	// Characters
	A = GLFW_KEY_A,
	B = GLFW_KEY_B,
	C = GLFW_KEY_C,
	D = GLFW_KEY_D,
	E = GLFW_KEY_E,
	F = GLFW_KEY_F,
	G = GLFW_KEY_G,
	H = GLFW_KEY_H,
	I = GLFW_KEY_I,
	J = GLFW_KEY_J,
	K = GLFW_KEY_K,
	L = GLFW_KEY_L,
	M = GLFW_KEY_M,
	N = GLFW_KEY_N,
	O = GLFW_KEY_O,
	P = GLFW_KEY_P,
	Q = GLFW_KEY_Q,
	R = GLFW_KEY_R,
	S = GLFW_KEY_S,
	T = GLFW_KEY_T,
	U = GLFW_KEY_U,
	V = GLFW_KEY_V,
	W = GLFW_KEY_W,
	X = GLFW_KEY_X,
	Y = GLFW_KEY_Y,
	Z = GLFW_KEY_Z,
	
	
	// Numbers
	NUM_0 = GLFW_KEY_0,
	NUM_1 = GLFW_KEY_1,
	NUM_2 = GLFW_KEY_2,
	NUM_3 = GLFW_KEY_3,
	NUM_4 = GLFW_KEY_4,
	NUM_5 = GLFW_KEY_5,
	NUM_6 = GLFW_KEY_6,
	NUM_7 = GLFW_KEY_7,
	NUM_8 = GLFW_KEY_8,
	NUM_9 = GLFW_KEY_9,


};

enum InputStatus {
	BEGIN = GLFW_PRESS,
	END = GLFW_RELEASE
};

class Engine
{
	GLFWwindow* Screen;

	
	std::unordered_map<size_t, size_t> keyStatus;
	virtual bool Start();
	virtual bool Update(float deltaTime);
	virtual void End();
	virtual void keyboardInput(keyCode Key, InputStatus Status);
	void PollEvents();

	

	void gameLoop();
	void Terminate();

	float LastTime = 0;
protected:
	float upTime = 0;
	Camera CurrentCam;
	Skybox Sky;

public:
	void Build(int width, int height, const char* Title);
};

