#pragma once
#include "CollisionShape.h"
#include "../Graphics/Vertex.h"
class CollisionOBB : public CollisionShape
{
public:
	CollisionOBB();
	CollisionOBB(std::vector<glm::vec3> v);
	~CollisionOBB();
	std::vector<glm::vec3> verticies;

};

