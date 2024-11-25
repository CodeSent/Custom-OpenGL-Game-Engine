#pragma once
#include <string>
#include <vector>

struct Vec2 {
	float x, y;
};

struct Vec3 {
	float x, y, z;
};

struct Vec4 {
	float x, y, z, w;
};
struct vPoints {
	Vec3 p;
	Vec3 n;
	Vec2 t;
};

class objLoader
{

	std::vector<std::string> divideString(std::string Line, char Divider);
	void parseData(std::string Line);
	void setData(std::string Line);
	void processVertex(std::vector<std::string> VertexRaw);
	bool DataCollectionStep = false;

public:
	bool Loaded = false;
	std::vector<Vec3> Vertices;
	std::vector<Vec3> Normals;
	std::vector<Vec2> Texture;
	std::vector<vPoints> facesData;

	void loadData(std::string FilePath);
	void clearData();
};

