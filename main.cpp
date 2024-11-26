#include <iostream>
#include "Source/Engine.h"
#include "Source/Objects.h"
#include "Source/Mesh.h"






float Rotation = 15.0f;



class TestGame : public Engine {

	Plane GrassTerrain;
	staticMesh MeshTest;
	staticMesh Cube;
	staticMesh Sword;
	float alpha;
	lightObject* Red;
	lightObject* Green;
	lightObject* Blue;
	lightObject* White;

	bool Start()
	{

		GrassTerrain.Transformation.size = { 1000,1000,1000 };
		GrassTerrain.Tex.Load("Textures/Grass.png");
		GrassTerrain.Process();

		Cube.Load("Models/cube.obj");
		Cube.Tex.Load("Textures/crate.png");
		Cube.Transformation.size= { 2,2,2 };
		Cube.Transformation.position.y += 2.5;




		Red =  gameLighting::createLightSource({ 7.5f,5.0f, 0.0f }, { 1.0f,0.0f,0.0f }, SPOT);
		Green = gameLighting::createLightSource({-7.5f,5.0f, 0.0f }, { 0.0f,1.0f,0.0f }, SPOT);
		Blue = gameLighting::createLightSource({ 0.0f,5.0f, 7.5f }, { 0.0f,0.0f,1.0f }, SPOT);
		White = gameLighting::createLightSource({ 0.0f,5.0f,-7.5f}, { 1.0f,1.0f,1.0f }, SPOT);

		alpha = 0.0f;

		gameLighting::SunDir = { 0.0f,-0.0f,1.0f };
		

		Sword.Load("Models/Sword.obj");
		Sword.Tex.Load("Textures/Sword_Diffuse.png");
		Sword.Transformation.size = { 4.0f,4.0f,4.0f };
		Sword.Transformation.position = { 2.5f,2.5f,5.0f };


		//Red->Quadratic = 0.01;
		
		


		//TextureTest2.Process();

		return true;
	}

	bool Update(float deltaTime)
	{
		GrassTerrain.Draw();

		Cube.Transformation.rotation.y += deltaTime * Rotation;


		Red->Dir = { std::cos(alpha),-1.0f,std::sin(alpha)};
		Blue->Dir = { std::cos(-alpha),-1.0f,std::sin(-alpha) };
		Green->Dir = { std::cos(alpha),-1.0f,std::sin(alpha) };
		White->Dir = { std::cos(-alpha),-1.0f,std::sin(-alpha) };

		alpha += deltaTime;

		Cube.Draw();
		//Sword.Draw();



		return true;
	}

	void keyboardInput(keyCode Key)
	{
		switch (Key)
		{
		case E:
			
		default:
			break;
		}
	}

	void End()
	{
		GrassTerrain.Delete();
		

	}
};


int main() {

	//std::cout << "Hello World!" << "\n";

	TestGame Game;
	Game.Build(750, 600, "Game");

	return 0;
}