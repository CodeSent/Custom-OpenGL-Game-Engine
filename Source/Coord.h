#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

struct Coord3D
{
	Coord3D* Anchor = nullptr;
	glm::vec3 position = {0.0f, 0.0f, 0.0f}, rotation = { 0.0f, 0.0f, 0.0f };
	virtual glm::mat4x4  getModelMatrix();
};

struct Geomerty3D : public Coord3D {
	glm::vec3 size = { 1.0f,1.0f,1.0f };
	glm::mat4x4  getModelMatrix() override;
};