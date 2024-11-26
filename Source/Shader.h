#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <glm.hpp>

struct ShaderInfo {
	//mutable std::unordered_map<const char* , int> UniformCache;
	unsigned int ID;
	bool Created;
};

class Shader
{
	ShaderInfo* ShaderSelected = nullptr;
	static std::unordered_map<std::string, ShaderInfo> Storage;
	static std::vector<std::string> Errors;

	static void QuerryErrors(unsigned int &Target,unsigned int Type);
	static void DisplayErrors();
	static void ComplieShader(unsigned int &Target,std::string Src,unsigned int Type);
	static void CreateShader(ShaderInfo& Target,std::string Dirctory);
	static std::string ReadFile(std::string File);
public:
	void Build(std::string ShaderDirct);
	void Bind(bool State);
	void Delete();
	static void DeleteAll();
	int getUniformLocation(const char* Name) const;

	void setUniform(const char* Name, int Value);
	void setUniform(const char* Name, unsigned int Value);
	void setUniform(const char* Name, float Value);
	void setUnifrom(const char* Name, bool Value);
	void setUniform(const char* Name, glm::vec3 Value);
	void setUnifrom(const char* Name, glm::mat4x4 Value);



};


