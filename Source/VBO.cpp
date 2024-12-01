#include "VBO.h"
#include <GL/glew.h>

void VBO::compileData(size_t Size, float* Begin)
{
	Bind(true);
	glBufferData(GL_ARRAY_BUFFER, Size, Begin, GL_STATIC_DRAW);
}

void VBO::Create()
{
	if (Created) return;
	glGenBuffers(1, &VBO_id);
	Created = true;
}

void VBO::Bind(bool State)
{
	if (!Created) return;
	glBindBuffer(GL_ARRAY_BUFFER, VBO_id * size_t(State));
}



void VBO::Delete()
{
	if (!Created) return;
	glDeleteBuffers(1, &VBO_id);
	Created = false;
}
