#include "Light.h"
#include <string>
#include <sstream>



std::unordered_map<size_t, lightObject> gameLighting::LightsInScene;
size_t gameLighting::totalLights = 0;
glm::vec3 gameLighting::SunDir = { 0.0f,1.0f,0.5f };

glm::vec3 Light::SunDir = {0.0f,1.0f,0.5f};

void Light::setUnifroms(Shader& objShader)
{
	//setSunUnifroms(objShader);
}

void Light::setSunUnifroms(Shader& objShader)
{
	glm::vec3 Color = { 1.0f,1.0f,1.0f }, Pos = { 7.5f,15.0f,10.0f };
	float Am = 0.1f, Diff = 0.8f, Spec = 1.0f;

	objShader.setUniform("Sun.lColor", Color);
	//objShader.setUniform("Sun.Pos", Pos);

	objShader.setUniform("Sun.Am", Am);
	objShader.setUniform("Sun.Diff", Diff);
	objShader.setUniform("Sun.Spec", Spec);

	objShader.setUniform("Sun.Dir", SunDir);
}

void gameLighting::setSunUnifroms(Shader& objShader)
{
	glm::vec3 Color = { 1.0f,1.0f,1.0f }, Pos = { 7.5f,15.0f,10.0f };
	float Am = 0.1f, Diff = 0.8f, Spec = 1.0f;

	objShader.setUniform("Sun.lColor", Color);
	//objShader.setUniform("Sun.Pos", Pos);

	objShader.setUniform("Sun.Am", Am);
	objShader.setUniform("Sun.Diff", Diff);
	objShader.setUniform("Sun.Spec", Spec);

	objShader.setUniform("Sun.Dir", SunDir);
}

lightObject* gameLighting::createLightSource()
{
	lightObject& light = LightsInScene[totalLights];
	totalLights++;
	return &light;
}

lightObject* gameLighting::createLightSource(glm::vec3 Pos)
{
	lightObject& light = LightsInScene[totalLights];
	light.Pos = Pos;
	totalLights++;
	return &light;
}

lightObject* gameLighting::createLightSource(glm::vec3 Pos, glm::vec3 Color)
{
	lightObject& light = LightsInScene[totalLights];
	light.Pos = Pos;
	light.Color = Color;
	totalLights++;
	return &light;
}

lightObject* gameLighting::createLightSource(lightType Type)
{
	lightObject& light = LightsInScene[totalLights];
	light.Type = Type;
	totalLights++;
	return &light;
}

lightObject* gameLighting::createLightSource(glm::vec3 Pos, lightType Type)
{
	lightObject& light = LightsInScene[totalLights];
	light.Type = Type;
	light.Pos = Pos;
	totalLights++;
	return &light;
}

lightObject* gameLighting::createLightSource(glm::vec3 Pos, glm::vec3 Color, lightType Type)
{
	lightObject& light = LightsInScene[totalLights];
	light.Type = Type;
	light.Pos = Pos;
	light.Color = Color;
	totalLights++;
	return &light;
}

void gameLighting::setUnifroms(Shader& objShader)
{
	setSunUnifroms(objShader);

	size_t maxLights = std::min(totalLights, size_t(256));
	std::string lightsLoc = "Lights";
	size_t index = 0;
	for (auto& I : LightsInScene) {

		lightObject& light = I.second;
		
		if (index >= size_t(256)) break;

		
		std::string StringIndex = std::to_string(index);

		std::stringstream Buf;
		Buf << lightsLoc;
		Buf << "[";
		Buf << (StringIndex + "]");
		std::string currentIndex = Buf.str();
		
		std::string lC = currentIndex + ".lColor";
		//std::cout << lC.c_str() << "\n";
		objShader.setUniform(lC.c_str(), light.Color);


		std::string lP = currentIndex + ".Pos";
		objShader.setUniform(lP.c_str(), light.Pos);

		std::string lDir = currentIndex + ".Dir";
		objShader.setUniform(lDir.c_str(), light.Dir);


		std::string lAm = currentIndex + ".Am";
		objShader.setUniform(lAm.c_str(), light.Am);

		std::string lDiff = currentIndex + ".Diff";
		objShader.setUniform(lDiff.c_str(), light.Diff);

		std::string lSpec = currentIndex + ".Spec";
		objShader.setUniform(lSpec.c_str(), light.Spec);


		std::string lQuad = currentIndex + ".Quadratic";
		objShader.setUniform(lQuad.c_str(), light.Quadratic);

		std::string lLine = currentIndex + ".Linear";
		objShader.setUniform(lLine.c_str(), light.Linear);


		std::string lConst = currentIndex + ".Constant";
		objShader.setUniform(lConst.c_str(), light.Constant);

		std::string lType = currentIndex + ".Type";
		objShader.setUniform(lType.c_str(), size_t(light.Type));

		std::string lEnabled = currentIndex + ".Enabled";
		objShader.setUniform(lEnabled.c_str(), size_t(light.Enabled));

		index++;
	}

	objShader.setUniform("total_Lights", maxLights);
}
