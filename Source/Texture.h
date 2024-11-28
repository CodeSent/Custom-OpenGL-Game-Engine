#pragma once
#include <string>
#include <unordered_map>


struct TexData {
	unsigned int Id;
	short TextureSlot = -1;
	bool created;
};

enum TextureType {
	COLOR,
	NORMAL,
	SPECULAR,
};

class Texture
{
	static std::unordered_map<std::string, TexData> Storage;
	static void LoadTexture(TexData &Target,std::string File,TextureType Type);
	static const std::string DefaultTexture;
public:
	TexData* TextureSelected;
	void Load(std::string File,TextureType TexType);
	void Load(std::string File);
	void Load();
	short Bind(bool State);
	void Delete();
	static void DeleteAll();
};

