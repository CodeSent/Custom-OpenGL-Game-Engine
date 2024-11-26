#include <GL/glew.h>
#include <sstream>
#include <fstream>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Shader.h"



static void GL_ClErr() { while (glGetError() != GL_NO_ERROR); }
static bool Gl_ChckErr(const char* Function, int Line) {
	while (GLenum Error = glGetError())
	{
		const char* E = (const char*)Error;
		const char* F = (const char*)Function;
		const char* L = (const char*)Line;
		std::cout << ":: [OpenGL Error] (" << Error << ") [Line:" << Line << "] \n" << F;
		return false;
	}
	return true;
}


#define Assert(x) if (!(x)) __debugbreak()

#define Check(X) \
 GL_ClErr();\
X;\
Assert(Gl_ChckErr(#X, __LINE__));



std::unordered_map<std::string, ShaderInfo> Shader::Storage;
std::vector<std::string> Shader::Errors;

void Shader::Build(std::string ShaderDirct)
{
	ShaderInfo& ShaderFound = Storage[ShaderDirct];
	if (!ShaderFound.Created) {
		CreateShader(ShaderFound,ShaderDirct);
	}
	ShaderSelected = &ShaderFound;
}


void Shader::QuerryErrors(unsigned int& Target, unsigned int Type)
{
	std::string TypeFile = "Vertex Shader:\n";
	if (Type == GL_FRAGMENT_SHADER) TypeFile = "Fragment Shader:\n";

	int result;
	glGetShaderiv(Target, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		Errors.push_back(TypeFile);

		int Length;
		glGetShaderiv(Target, GL_INFO_LOG_LENGTH, &Length);
		char* Message = (char*) alloca(Length * sizeof(Length));
		glGetShaderInfoLog(Target, Length, &Length, Message);

		std::string StrStore(Message);
		Errors.push_back(Message);
	}
}

void Shader::DisplayErrors()
{
	if (Errors.size() > 0) {
		std::cout << ":: Shader Complied with Errors. ::" << "\n";
		std::cout << "|ERROR REPORT:=======================================================|" << "\n\n";
		for (auto I : Errors) {
			std::cout << I << "\n";
		}
		std::cout << "|====================================================================|" << "\n";
		Errors.clear();
	}
}

void Shader::ComplieShader(unsigned int& Target, std::string Src, unsigned int Type)
{
	std::string TypeFile = "Vertex.glsl";
	if (Type == GL_FRAGMENT_SHADER) TypeFile = "Fragment.glsl";

	std::string Source = ReadFile(Src + "/" + TypeFile);
	const char* cSource = Source.c_str();

	Target = glCreateShader(Type);
	glShaderSource(Target, 1, &cSource, nullptr);
	glCompileShader(Target);

	QuerryErrors(Target, Type);


}

void Shader::CreateShader(ShaderInfo& Target, std::string Dirctory)
{
	Target.ID = glCreateProgram();

	Errors.clear();

	unsigned int vS, fS;
	ComplieShader(vS, Dirctory, GL_VERTEX_SHADER);
	ComplieShader(fS, Dirctory, GL_FRAGMENT_SHADER);
	DisplayErrors();

	glAttachShader(Target.ID, vS);
	glAttachShader(Target.ID, fS);
	glLinkProgram(Target.ID);
	glValidateProgram(Target.ID);

	glDeleteShader(vS);
	glDeleteShader(fS);


	Target.Created = true;


}

std::string Shader::ReadFile(std::string File)
{
	std::ifstream FileOBJ;
	std::string Output = "";
	FileOBJ.open(File);

	if (FileOBJ.is_open()) {
		std::string VLine;
		while (std::getline(FileOBJ, VLine)) {
			VLine += "\n";
			Output += VLine;
		}
	}

	return Output;

}



void Shader::Bind(bool State)
{


	if (ShaderSelected == nullptr) return;
	if (!(ShaderSelected->Created)) return;

	//std::cout << "Shader :" << ShaderSelected->ID << " Binding :" << State << "\n";

	glUseProgram(ShaderSelected->ID * unsigned int(State));
}

void Shader::Delete()
{
	if (ShaderSelected == nullptr) return;
	if (!(ShaderSelected->Created)) return;
	//ShaderSelected->UniformCache.clear();

	glDeleteProgram(ShaderSelected->ID);
}

void Shader::DeleteAll()
{
	for (auto& I : Storage) {
		auto& OBJ = I.second;
		if (!OBJ.Created) continue;
		//OBJ.UniformCache.clear();
		glDeleteProgram(OBJ.ID);
		OBJ.Created = false;
	}
}

int Shader::getUniformLocation(const char* Name)  const
{
	if (ShaderSelected == nullptr) return -1;
	if (!(ShaderSelected->Created)) return -1;
	
	//if (ShaderSelected->UniformCache.find(Name) != ShaderSelected->UniformCache.end()) {

	//	int LOC = ShaderSelected->UniformCache[Name];
	//	std::cout << Name << ":" << LOC << "\n";
	//	return LOC;
	//}
	
	int Loc = glGetUniformLocation(ShaderSelected->ID, Name);
	
	if (Loc != -1) {
		
		//ShaderSelected->UniformCache[Name] = Loc;
	}
	else {
		std::cout << "Got Uniform Location Request, that doesnt exist :" << Name << "\n";
	}
	return Loc;
}

void Shader::setUniform(const char* Name,int Value)
{
	int Pos = getUniformLocation(Name);
	if (Pos >= 0) {
		Bind(true);
		glUniform1i(Pos,Value);
	}
}

void Shader::setUniform(const char* Name, unsigned int Value)
{
	int Pos = getUniformLocation(Name);
	if (Pos >= 0) {
		Bind(true);
		//std::cout << Name << ":" << Value << "\n";
		glUniform1ui(Pos, Value);
	}
}

void Shader::setUniform(const char* Name, float Value)
{
	int Pos = getUniformLocation(Name);
	if (Pos >= 0) {
		Bind(true);
		Check(glUniform1f(Pos, Value));
	}
}

void Shader::setUnifrom(const char* Name, bool Value)
{
	int Pos = getUniformLocation(Name);
	if (Pos >= 0) {
		Bind(true);
		glUniform1ui(Pos, Value);
	}
}

void Shader::setUniform(const char* Name, glm::vec3 Value)
{
	int Pos = getUniformLocation(Name);
	if (Pos >= 0) {
		Bind(true);
		glUniform3f(Pos, Value.x, Value.y, Value.z);
	}
}

void Shader::setUnifrom(const char* Name, glm::mat4x4 Value)
{
	int Pos = getUniformLocation(Name);
	if (Pos >= 0) {
		Bind(true);
		glUniformMatrix4fv(Pos,1,GL_FALSE,glm::value_ptr(Value));
	}
}
