
#include <iostream>
#include <GL\glew.h>
#include "Objects.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"


#include "Engine.h"



void Engine::Build(int width, int height, const char* Title)
{
	

	if (glfwInit()) {

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		Screen = glfwCreateWindow(width, height, Title, 0, 0);
		glfwMakeContextCurrent(Screen);
		glewInit();

		std::cout << "Glass Framework Game Engine, OpenGL Version: " << glGetString(GL_VERSION) << "\n";
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//glClearColor(1.0f, 1.0f, 0.17f, 1.0f);
		CurrentCam.Height = height;
		CurrentCam.Width = width;
		//CurrentCam.Fov = 90;
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glFrontFace(GL_CW);
		Skybox::cam;
		Sky = Skybox("Textures/skybox1");
		
		bool Continue = Start();
		

		LastTime = (float) glfwGetTime();
		

		if (Continue) {
			gameLoop();
		}
		Terminate();

	}


	

}


void Engine::gameLoop()
{
	bool Running = true;
	while (!glfwWindowShouldClose(Screen) and Running)
	{
		int w, h;
		glfwGetWindowSize(Screen, &w, &h);
		glViewport(0, 0, w, h);

		PollEvents();

		float CurrentTime = (float)glfwGetTime();
		float DeltaTime = CurrentTime - LastTime;

		CurrentCam.Matrix(Object::CameraMatrix);
		CurrentCam.Matrix(staticMesh::CameraMatrix);
		CurrentCam.Inputs(Screen);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		CurrentCam.Matrix(Skybox::cam);
		Sky.render();

		Running = Update(DeltaTime);


		glfwSwapBuffers(Screen);
		glfwPollEvents();

		LastTime = CurrentTime;
	}

}

void Engine::Terminate()
{
	staticMesh::DeleteAll();

	Sky.Delete();
	Shader::DeleteAll();
	Texture::DeleteAll();
	glfwDestroyWindow(Screen);
	glfwTerminate();
}



bool Engine::Start()
{
	return false;
}

bool Engine::Update(float deltaTime)
{
	return false;
}

void Engine::End()
{
}

void Engine::keyboardInput(keyCode Key, InputStatus Status)
{

}

void Engine::PollEvents()
{
	for (size_t i = GLFW_KEY_SPACE; i < 349; i++) {
		if (keyStatus[i] == 0) keyStatus[i] = GLFW_RELEASE;
		size_t currentkeyStatus = glfwGetKey(Screen, i);
		if (currentkeyStatus != keyStatus[i]) {
			keyboardInput(keyCode(i), InputStatus(currentkeyStatus));
			keyStatus[i] = currentkeyStatus;
		}
	}
	
}

