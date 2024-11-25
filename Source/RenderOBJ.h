#pragma once
#include "Shader.h"
#include "Texture.h"
#include <vector>
#include "Types.h"



class RenderOBJ
{
	unsigned int VAO, VBO, IBO,TriCount;

public:
	bool Created;
	void Build(float* Vertecies,size_t v_Size,unsigned int* Indecies, size_t I_Size,std::vector<VertexPointer> VAO_Data);


	void VertexPoint(VertexPointer Data);

	void beginDraw();

	void Push();

	void Delete();
};

