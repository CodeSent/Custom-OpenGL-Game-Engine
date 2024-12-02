#include <GL/glew.h>
#include "VertexArray.h"
#include <iostream>

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





void VertexArray::Create()
{
	if (Created) return;
	glGenVertexArrays(1, &VAO_id);
	Created = true;
}

void VertexArray::setAttributes( VertexPointer &Attributes)
{
	if (!Created) return;
	VertexPointer& data = Attributes;
	//std::cout << data.Index << " " << data.Length << " " << data.Type << " " << data.Stride << " " << data.Pointer << "\n";
	Check(glEnableVertexAttribArray(data.Index));
	Check(glVertexAttribPointer(data.Index, data.Length, data.Type, GL_FALSE, data.Stride, (const void*)data.Pointer));
}

void VertexArray::Bind(bool State)
{
	if (!Created) return;
	glBindVertexArray(VAO_id * size_t(State));
}

void VertexArray::Delete()
{
	if (!Created) return;
	glDeleteVertexArrays(1, &VAO_id);
}
