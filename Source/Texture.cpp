#include <GL/glew.h>
#include <iostream>
#include "STB/stb_image.h"
#include "Texture.h"


static void GL_ClErr() { while (glGetError() != GL_NO_ERROR); }
static bool Gl_ChckErr(const char* Function, int Line) {
	while (GLenum Error = glGetError())
	{
		const char* E = (const char*)Error;
		const char* F = (const char*)Function;
		const char* L = (const char*)Line;
		std::cout << ":: [OpenGL Error] (" << Error << ") [Line:" << Line << "] \n" << F << "\n";
		return false;
	}
	return true;
}


#define Assert(x) if (!(x)) __debugbreak()

#define Check(X) \
 GL_ClErr();\
X;\
Assert(Gl_ChckErr(#X, __LINE__));





std::unordered_map<std::string, TexData> Texture::Storage;
const std::string Texture::DefaultTexture = "Textures/Default.png";

void Texture::LoadTexture(TexData& Target, std::string File, TextureType Type)
{
	size_t TextureSlot = 0;
	size_t LOD = 0;
	size_t internalFormat = GL_RGBA;
	size_t Format = GL_RGBA;
	size_t colChannels = GL_RGBA;

	switch (Type)
	{
	case NORMAL:
	    TextureSlot = 2;
		internalFormat = GL_RGB;
	case COLOR:
		break;
	default:
		break;
	}


	int WidthImg, HeightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* Bytes = stbi_load(File.c_str(), &WidthImg, &HeightImg, &numColCh, 4);

	glGenTextures(1,&(Target.Id));
	glActiveTexture(GL_TEXTURE0+TextureSlot);
	glBindTexture(GL_TEXTURE_2D, Target.Id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glTexImage2D(GL_TEXTURE_2D, LOD, internalFormat, WidthImg, HeightImg, 0, Format, GL_UNSIGNED_BYTE, Bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(Bytes);

	Target.TextureSlot = TextureSlot;
	Target.created = true;


}

void Texture::Load(std::string File, TextureType TexType)
{
	TexData& DataSelected = Storage[File];
	if (!DataSelected.created) {
		LoadTexture(DataSelected, File, TexType);
	}
	TextureSelected = &DataSelected;
}

void Texture::Load(std::string File)
{
	TexData& DataSelected = Storage[File];
	if (!DataSelected.created) {
		LoadTexture(DataSelected, File,COLOR);
	}
	TextureSelected = &DataSelected;
}

void Texture::Load()
{
	TexData& DataSelected = Storage[DefaultTexture];
	if (!DataSelected.created) {
		LoadTexture(DataSelected, DefaultTexture, COLOR);
	}
	TextureSelected = &DataSelected;
}

short Texture::Bind(bool State)
{
	if (TextureSelected == nullptr) Load();
	if (!TextureSelected->created) Load();
	glActiveTexture(GL_TEXTURE0 + TextureSelected->TextureSlot);
	Check(glBindTexture(GL_TEXTURE_2D, TextureSelected->Id * unsigned int(State)));

	return ((TextureSelected->TextureSlot + 1) * short(State)) - 1;
}

void Texture::Delete()
{
	if (TextureSelected == nullptr) return;
	if (!TextureSelected->created) return;
	glDeleteTextures(1, &(TextureSelected->Id));
	TextureSelected->created = false;

}

void Texture::DeleteAll()
{
	for (auto& I : Storage) {
		auto& OBJ = I.second;
		if (!OBJ.created) continue;
		glDeleteTextures(1, &(OBJ.Id));
		OBJ.created = false;
	}
}
