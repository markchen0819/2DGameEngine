#pragma once
#include "ShapeType.h"
#include "../Debug/CollisionAreaObject.h"


class CollisionShape
{
public:
	ShapeType Type;
	CollisionShape();
	~CollisionShape();

	void SetScale(glm::vec3 s);
	glm::vec3 GetScale();
private:
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
};

