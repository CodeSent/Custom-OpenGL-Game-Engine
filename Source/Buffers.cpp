#include <GL/glew.h>
#include <iostream>
#include "Buffers.h"


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






void Buffer::ComplieData(size_t Size, void* Start)
{
	Check(glBufferData(int(Type), Size, Start, GL_STATIC_DRAW));
}

void Buffer::Create(BufferType bufferType)
{
	if (Created) return;


	glGenBuffers(1, &bufferId);
	Created = true;
	Type = bufferType;
}



void Buffer::Bind(bool State)
{
	if (!Created) return;


	glBindBuffer(int(Type), bufferId * size_t(State));
}


void Buffer::Delete()
{
	if (!Created) return;
	glDeleteBuffers(1, &bufferId);
	Created = false;
}
