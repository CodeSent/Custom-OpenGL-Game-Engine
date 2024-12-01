#include <iostream>
#include "Source/Engine.h"
#include "Source/Objects.h"
#include "Source/Mesh.h"






float Rotation = 15.0f;



class TestGame : public Engine {

	Plane GrassTerrain;
	staticMesh MeshTest;
	staticMesh Cube;
	staticMesh Cube2;
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

		

	
	
		
		Cube.Load("Models/Axe.obj");
		Cube.objMaterial.colorMap.Load("Textures/Axe_UV.png", COLOR);
		Cube.Transformation.size = { 7.5,5,10 };

		


		Red =  gameLighting::createLightSource({ 0.0f,2.5f, 1.0f }, { 1.0f,1.0f,1.0f }, POINT);
		FlashLight = gameLighting::createLightSource({ 0.0f,0.0f, 0.0f }, { 1.0f,1.0f,1.0f }, SPOT);

		FlashLight->Enabled = false;
		FlashLight->Constant = 0.1;

		Red->Constant = 0.25;



		alpha = 0.0f;

		gameLighting::SunDir = { 0.0f,0.0f,0.0f };
		

		//Sword.Load("Models/Sword.obj");
		//Sword.objMaterial.colorMap.Load("Textures/Sword_Diffuse.png");
		//Sword.Transformation.size = { 4.0f,4.0f,4.0f };
		//Sword.Transformation.position = { 2.5f,2.5f,5.0f };


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
		//Axe.Draw();




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
			break;
		};

		case T:
		{
			if (Status == BEGIN) {
				CurrentCam.FreezeOri = !CurrentCam.FreezeOri;
			}

			break;
		};
		default:
			break;
		}
	}

	void End()
	{
		//GrassTerrain.Delete();

	}
};


int main() {

	//std::cout << "Hello World!" << "\n";

	TestGame Game;
	Game.Build(750, 600, "Game");

	return 0;
}