#include <gl/glew.h>
#include "STB/stb_image.h"
#include <gtc/type_ptr.hpp>
#include "Skybox.h"
#include <iostream>







CamMat Skybox::cam;


Skybox::Skybox(const char* Folder)
{
	skyboxTextureFolder = Folder;
}

void Skybox::process()
{
	const char* ShaderDir = "Shaders/Skybox/Shader1";
	skyboxShader.Build(ShaderDir);

	float Vertex[6] = {
		-1.0f, 3.0f, 
		 3.0f,-1.0f,
		-1.0f,-1.0f,
	};
	unsigned int index[3] = {
		2,1,0
	};


	glGenVertexArrays(1, &(dataIds.Vao));
	glGenBuffers(1, &(dataIds.Vbo));
	glGenBuffers(1, &(dataIds.ibo));

	glBindVertexArray(dataIds.Vao);

	glBindBuffer(GL_ARRAY_BUFFER, dataIds.Vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), Vertex, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dataIds.ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*)0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


}

void Skybox::Bind(bool Enable)
{
	skyboxShader.Bind(Enable);
	glBindBuffer(GL_ARRAY_BUFFER, unsigned int(Enable) * dataIds.Vbo);
	glBindVertexArray(unsigned int(Enable) * dataIds.Vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, unsigned int(Enable) * dataIds.Cubemap);
	
}

void Skybox::loadSkyboxTexture()
{


	std::string Sides[6] = {
		skyboxTextureFolder + "/right.png",
		skyboxTextureFolder + "/left.png",
		skyboxTextureFolder + "/top.png",
		skyboxTextureFolder + "/bottom.png",
		skyboxTextureFolder + "/front.png",
		skyboxTextureFolder + "/back.png",
	};

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, dataIds.Cubemap);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (unsigned int i = 0; i < 6; i++) {
		int height, width, nrChannels;
		GLenum Ty = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
		const char* Line = Sides[i].c_str();
		//Line = "Textures/Default.png";
		unsigned char* data = stbi_load(Line, &width, &height, &nrChannels, 4);
		if (data) {

			if (i == 0) {

			}
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D(Ty, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else {
			std::cout << "Failed to load Texture: " << Sides[i] << "\n";
		}
	}


}


void Skybox::render()
{
	if (!Complied) {
		loadSkyboxTexture();
		process();
		Complied = true;
	}




	glDisable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glm::mat4x4 Mat = glm::mat4x4(glm::mat3x3(cam.View));
	glm::mat4x4 invVPmat = glm::inverse(cam.Proj * Mat);
	Bind(true);
//	int mLoc = skyboxShader.getUniformLocation("m_invProjView");
//	if (mLoc == -1) std::cout << "Unfiform not found. \n";
//	glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(invVPmat));
	skyboxShader.setUnifrom("m_invProjView", invVPmat);
	glActiveTexture(GL_TEXTURE0);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	Bind(false);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

}

void Skybox::Delete()
{

}
