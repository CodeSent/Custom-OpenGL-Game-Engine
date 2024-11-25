#include <GL/glew.h>
#include <iostream>
#include "RenderOBJ.h"

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





void RenderOBJ::Build(float* Vertecies, size_t v_Size, unsigned int* Indecies, size_t I_Size, std::vector<VertexPointer> VAO_Data)
{
	if (Created) return;
	
	TriCount = I_Size;

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, v_Size* sizeof(float), Vertecies, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, I_Size* sizeof(unsigned int), Indecies, GL_STATIC_DRAW);
	for (auto I : VAO_Data) {
		VertexPoint(I);
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	Created = true;

}

void RenderOBJ::VertexPoint(VertexPointer Data)
{
	//std::cout << "Vertex Ptr Data: " << Data.Index << " " << Data.Length << " " << Data.Type << " " << Data.Stride << " " << Data.Pointer << "\n";
	glEnableVertexAttribArray(Data.Index);
	glVertexAttribPointer(Data.Index, Data.Length, Data.Type, GL_FALSE, Data.Stride, (const void*)Data.Pointer);

}
















void RenderOBJ::beginDraw()
{
	if (!Created) return;
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

}


void RenderOBJ::Push()
{
	//int S_bind, T_Bind;
	//glGetIntegerv(GL_TEXTURE_BINDING_2D, &T_Bind);
	//glGetIntegerv(GL_CURRENT_PROGRAM, &S_bind);
	//std::cout << "Shader Binded: " << S_bind << " Texture Binded : " << T_Bind << ". \n";
	Check(glDrawElements(GL_TRIANGLES, TriCount, GL_UNSIGNED_INT, 0));
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


}









void RenderOBJ::Delete()
{
	if (!Created) return;
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteVertexArrays(1, &VAO);
	Created = false;
}
