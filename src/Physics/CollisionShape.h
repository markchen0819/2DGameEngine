#pragma once
#include "ShapeType.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class CollisionShape
{
public:
	CollisionShape();
	~CollisionShape();

	void SetScale(glm::vec3 s);
	glm::vec3 GetScale();

	ShapeType Type;

private:
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
};

