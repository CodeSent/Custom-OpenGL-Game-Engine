#include "VAO.h"
#include <GL/glew.h>
#include <iostream>

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





void VAO::Create()
{
	if (Created) return;
	glGenVertexArrays(1, &VAO_id);
	Created = false;
}

void VAO::setAttributes(VBO& Target, VertexPointer Attributes[])
{
	if (!Created) return;
	Bind(true);
	Target.Bind(true);
	for (size_t i = 0; (size_t(Attributes) / sizeof(VertexPointer)) > i;i++) {
		VertexPointer& data = Attributes[i];
		Check(glEnableVertexAttribArray(data.Index));
		Check(glVertexAttribPointer(data.Index, data.Length, data.Type, GL_FALSE, data.Stride, (const void*)data.Pointer));
	}
	Bind(false);
	Target.Bind(false);
}

void VAO::Bind(bool State)
{
	if (!Created) return;
	glBindVertexArray(VAO_id * size_t(State));
}

void VAO::Delete()
{
	if (!Created) return;
	glDeleteVertexArrays(1, &VAO_id);
}
