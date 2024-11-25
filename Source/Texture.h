#pragma once
#include <string>
#include <unordered_map>


struct TexData {
	unsigned int Id;
	bool created;
};

class Texture
{
	TexData* TextureSelected;
	static std::unordered_map<std::string, TexData> Storage;
	static void LoadTexture(TexData &Target,std::string File);
	static const std::string DefaultTexture;
public:
	void Load(std::string File);
	void Load();
	void Bind(bool State);
	void Delete();
	static void DeleteAll();
};

