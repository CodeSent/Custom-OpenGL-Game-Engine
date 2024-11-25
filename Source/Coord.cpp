#include "Coord.h"

glm::mat4x4 Coord3D::getModelMatrix()
{
	glm::mat4x4 Model(1.0f);

	Model = glm::translate(Model, position);

	Model = glm::rotate(Model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	Model = glm::rotate(Model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	Model = glm::rotate(Model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	

	return Model;
}

glm::mat4x4 Geomerty3D::getModelMatrix()
{
	glm::mat4x4 Model(1.0f);

	Model = glm::translate(Model, position);

	Model = glm::rotate(Model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	Model = glm::rotate(Model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	Model = glm::rotate(Model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	Model = glm::scale(Model, size + glm::vec3(0.0f,0.001f,0.0f));

	return Model;
}
