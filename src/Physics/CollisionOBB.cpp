#include "CollisionOBB.h"

CollisionOBB::CollisionOBB()
{
	Type = ShapeType::OBB;
}

CollisionOBB::CollisionOBB(std::vector<glm::vec3> v)
{
	verticies = v;
}

CollisionOBB::~CollisionOBB()
{
	verticies.clear();
}
