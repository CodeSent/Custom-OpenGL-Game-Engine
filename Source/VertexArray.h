#pragma once
#include "Types.h"

class VertexArray
{
	size_t VAO_id;
	bool Created = false;
public:
	void Create();
	void setAttributes(VertexPointer &Attributes);
	void Bind(bool State);
	void Delete();
	
};

