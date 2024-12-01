#pragma once
#include "Types.h"
#include "VBO.h"

class VAO
{
	size_t VAO_id;
	bool Created = false;
public:
	void Create();
	void setAttributes(VBO & Target,VertexPointer Attributes[]);
	void Bind(bool State);
	void Delete();
	
};

