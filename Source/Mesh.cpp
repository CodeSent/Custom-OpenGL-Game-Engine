#include <GL/glew.h>
#include "Mesh.h"



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



VertexPointer staticMesh::Atributes[] = {
		{0, 3, GL_FLOAT, sizeof(vertexData), 0},
		{1, 3, GL_FLOAT, sizeof(vertexData), 3 * sizeof(float)},
		{2, 2, GL_FLOAT, sizeof(vertexData), 6 * sizeof(float)}
};
CamMat staticMesh::CameraMatrix;
std::string staticMesh::ShaderFile = "Shaders/3D/ShaderV2";
Light staticMesh::Sun;
std::unordered_map<std::string, MeshData> staticMesh::MeshStorage;

void staticMesh::buildModel(MeshData& Data, std::string filePath)
{
	if (!Data.mainData.Loaded) Data.mainData.loadData(filePath);
	std::vector<vPoints>& VertexData = Data.mainData.facesData;

	std::cout << "Complied a Mesh" << "\n";
//	int Index = 0;
	//for (auto& I : VertexData) {
	//	std::cout << Index << ":" << "(" << I.p.x << "," << I.p.y << "," << I.p.z << "):(" << I.n.x << "," << I.n.y << "," << I.n.z << "):(" << I.t.x << "," << I.t.y << ")" << "\n";
	//	Index++;
	//}

	float* Start = &(VertexData[0].p.x);
	glGenVertexArrays(1, &(Data.VAO));
	glBindVertexArray(Data.VAO);
	glGenBuffers(1, &(Data.VBO));
	glBindBuffer(GL_ARRAY_BUFFER, Data.VBO);
	glBufferData(GL_ARRAY_BUFFER, VertexData.size() * sizeof(vPoints), Start, GL_STATIC_DRAW);
	for (VertexPointer data : Atributes) {
		Check(glEnableVertexAttribArray(data.Index));
		Check(glVertexAttribPointer(data.Index, data.Length, data.Type, GL_FALSE, data.Stride, (const void*)data.Pointer));
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	Data.Indecies = VertexData.size();
	Data.Created = true;
	

}



void staticMesh::setUniforms()
{
	glm::mat4 ModelMat = glm::mat4(1.0f);
	glm::mat4 ViewMat = glm::mat4(1.0f);
	glm::mat4 ProjMat = glm::mat4(1.0f);

	ModelMat = Transformation.getModelMatrix();

	ViewMat = CameraMatrix.View;
	ProjMat = CameraMatrix.Proj;

	objShader.setUnifrom("u_Model", ModelMat);
	objShader.setUnifrom("u_View", ViewMat);
	objShader.setUnifrom("u_Proj", ProjMat);

	//Sun.setUnifroms(objShader);
	gameLighting::setUnifroms(objShader);

	objShader.setUniform("camPos", CameraMatrix.CamPos);
	objShader.setUniform("lightInfluence", lightInfluence);

	objShader.setUniform("Tex0", 0);
}



void staticMesh::Load(std::string filePath)
{
	objShader.Build(ShaderFile);
	MeshData& DataSelected = MeshStorage[filePath];
	if (!DataSelected.Created) {
		buildModel(DataSelected, filePath);
	}
	Data = &DataSelected;
	
}

void staticMesh::Draw()
{
	if (Data == nullptr) return;
	if (!Data->Created) return;
	glBindVertexArray(Data->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, Data->VBO);
	objShader.Bind(true);
	Tex.Bind(true);
	setUniforms();
	Check(glDrawArrays(GL_TRIANGLES, 0, Data->Indecies));
	Tex.Bind(false);
	objShader.Bind(false);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void staticMesh::Delete()
{
	if (Data == nullptr) return;
	if (!Data->Created) return;
	glDeleteVertexArrays(1, &(Data->VAO));
	glDeleteBuffers(1, &(Data->VBO));
	Data->mainData.clearData();

	Data->Created = false;
}

void staticMesh::DeleteAll()
{
	for (auto& I : MeshStorage) {
		MeshData& dataToDel = I.second;
		if (!dataToDel.Created and !dataToDel.mainData.Loaded) return;
		glDeleteVertexArrays(1, &(dataToDel.VAO));
		glDeleteBuffers(1, &(dataToDel.VBO));
		dataToDel.mainData.clearData();

		dataToDel.Created = false;
	}
}

void staticMesh::preLoadModel(std::string filePath)
{
	MeshData& DataSelected = MeshStorage[filePath];
	if (!DataSelected.mainData.Loaded) {
		DataSelected.mainData.loadData(filePath);
	}
}

void staticMesh::preLoadModel(std::vector<std::string> filePaths)
{
	for (auto& I : filePaths) {
		preLoadModel(I);
	}
}
