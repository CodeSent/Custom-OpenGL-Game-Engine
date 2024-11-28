#include <fstream>
#include <iostream>
#include "Loader.h"

std::vector<std::string> objLoader::divideString(std::string Line, char Divider)
{
	std::vector<std::string> Parts;
	std::string Data;
	for (size_t i = 0; i < Line.length(); i++)
	{
		char Character = Line[i];
		if (Character == Divider) {
			if (Data.length() >= 1) Parts.push_back(Data);
		//	std::cout << Data << "|";
			Data = "";
		}
		else
		{
			Data += Character;
		}
		
	}
	//std::cout << "\n";
	return Parts;
}

void objLoader::parseData(std::string Line)
{
	if (Line.length() < 3) return;

	std::vector<std::string> PartedLine = divideString(Line,' ');
	std::string Prefex = PartedLine[0];
	if (Prefex == "v") {
		if (PartedLine.size() > 3) {
			Vec3 Vertex;
			Vertex.x = std::stof(PartedLine[1]);
			Vertex.y = std::stof(PartedLine[2]);
			Vertex.z = std::stof(PartedLine[3]);

			Vertices.push_back(Vertex);
		}
		
	}
	else if (Prefex == "vt") {
		if (PartedLine.size()  > 2) {
			Vec2 UV;
			UV.x = std::stof(PartedLine[1]);
			UV.y = std::stof(PartedLine[2]);


			Texture.push_back(UV);
		}
	}
	else if(Prefex == "vn") {
		if (PartedLine.size() > 3) {
			Vec3 Normal;
			Normal.x = std::stof(PartedLine[1]);
			Normal.y = std::stof(PartedLine[2]);
			Normal.z = std::stof(PartedLine[3]);

			Normals.push_back(Normal);
		}
	}
	else if (Prefex == "f") {
		DataCollectionStep = false;
	}
}

void objLoader::setData(std::string Line)
{
	if (Line.length() < 3) return;

	std::vector<std::string> PartedLine = divideString(Line,' ');
	std::string Prefex = PartedLine[0];

	if (Prefex == "f") {
		if (PartedLine.size() > 3) {
			
			std::vector<std::string> v1 = divideString(PartedLine[1] + "/",'/');
			std::vector<std::string> v2 = divideString(PartedLine[2] + "/", '/');
			std::vector<std::string> v3 = divideString(PartedLine[3] + "/", '/');

			processVertex(v1);
			processVertex(v2);
			processVertex(v3);
		}

	}

}

void objLoader::processVertex(std::vector<std::string> VertexRaw)
{
	if (VertexRaw.size() < 3) return;

	size_t vertexPoint, normalPoint, texturePoint;
	vertexPoint = size_t(std::stoi(VertexRaw[0]));
	texturePoint = size_t(std::stoi(VertexRaw[1]));
	normalPoint = size_t(std::stoi(VertexRaw[2]));


	vPoints main;
	main.p = Vertices[vertexPoint-1];
	main.n = Normals[normalPoint-1];
	main.t = Texture[texturePoint-1];

	


	facesData.push_back(main);

}

void objLoader::loadData(std::string File)
{
	clearData();

	std::ifstream FileOBJ;
	FileOBJ.open(File);

	if (FileOBJ.is_open()) {
		std::string VLine;
		DataCollectionStep = true;
		while (std::getline(FileOBJ, VLine)) {
			//std::cout << VLine << "\n";
			if (DataCollectionStep) {
				parseData(VLine + " ");
				if (DataCollectionStep) continue;
			}
			setData(VLine + " ");
		}
		Loaded = true;
	}


}

void objLoader::clearData()
{
	Vertices.clear();
	Normals.clear();
	Texture.clear();
	facesData.clear();
	Loaded = false;
}
