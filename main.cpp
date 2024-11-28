#include <iostream>
#include "Source/Engine.h"
#include "Source/Objects.h"
#include "Source/Mesh.h"






float Rotation = 15.0f;



class TestGame : public Engine {

	Plane GrassTerrain;
	staticMesh MeshTest;
	staticMesh Cube;
	staticMesh Axe;
	staticMesh Sword;
	float alpha = 0.0f;
	float cosAlpha = 0.0f;
	lightObject* Red;
	lightObject* Green;
	lightObject *FlashLight;

	bool Start()
	{

		GrassTerrain.Transformation.size = { 1000,1000,1000 };
		GrassTerrain.objMaterial.colorMap.Load("Textures/Grass.png");
		GrassTerrain.Process();

		Cube.Load("Models/cube.obj");
		Cube.objMaterial.colorMap.Load("Textures/crate.png",COLOR);
		Cube.objMaterial.NormalMap.Load("Textures/crate_Normal.png",NORMAL);
		Cube.objMaterial.SpecularMap.Load("Textures/crate_Specular.png", SPECULAR);
		Cube.Transformation.size= { 2,2,2 };
		Cube.Transformation.position.y += 2.5;

		Axe.Load("Models/stall.obj");
		Axe.objMaterial.colorMap.Load("Textures/stall_UV.png");
		Axe.objMaterial.NormalMap.Load("Textures/stall_UV_Normal.png",NORMAL);
		Axe.Transformation.size = { 7,7,7 };
		Axe.Transformation.position = {15.0f,0.0f,0.0f};

		


		Red =  gameLighting::createLightSource({ 10.0f,10.0f, 0.0f }, { 1.0f,1.0f,1.0f }, POINT);
		FlashLight = gameLighting::createLightSource({ 0.0f,0.0f, 0.0f }, { 1.0f,1.0f,1.0f }, SPOT);
		//Green = gameLighting::createLightSource({ 15.0f,7.5f,0.0f }, { 1.0f,0.0f,0.0f });

		FlashLight->Enabled = false;
		FlashLight->Linear = 0.0001;



		alpha = 0.0f;

		gameLighting::SunDir = { 0.5f,0.5f,0.5f };
		

		Sword.Load("Models/Sword.obj");
		Sword.objMaterial.colorMap.Load("Textures/Sword_Diffuse.png");
		Sword.Transformation.size = { 4.0f,4.0f,4.0f };
		Sword.Transformation.position = { 2.5f,2.5f,5.0f };


		//Red->Quadratic = 0.01;
		
		


		//TextureTest2.Process();

		return true;
	}

	bool Update(float deltaTime)
	{
		GrassTerrain.Draw();

		//Cube.Transformation.rotation.y += deltaTime * Rotation;



		alpha += deltaTime*0.5;


		//gameLighting::SunDir = { 0.0f,(1 + std::sin( alpha)) / 2,std::cos(alpha) };

		FlashLight->Pos = CurrentCam.Position;
		FlashLight->Dir = CurrentCam.Orientation;

		Cube.Draw();
		Axe.Draw();



		return true;
	}

	void keyboardInput(keyCode Key,InputStatus Status)
	{
		switch (Key)
		{
		case F:
		{
			if (Status == BEGIN) {
				FlashLight->Enabled = !(FlashLight->Enabled);
			}
		};
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