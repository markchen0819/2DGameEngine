#include "CollisionOBB.h"
#include <glm/gtx/euler_angles.hpp>

CollisionOBB::CollisionOBB()
{
	Type = ShapeType::OBB;
}

CollisionOBB::CollisionOBB(std::vector<glm::vec4> v)
{
	Type = ShapeType::OBB;
	verticies = v;
}

CollisionOBB::~CollisionOBB()
{
	verticies.clear();
}

glm::vec4 CollisionOBB::GetCenter()
{
	return center;
}

void CollisionOBB::SetCenter(glm::vec4 c)
{
	center = c;
}

glm::mat4 CollisionOBB::GetRotationMat()
{
	return rotation;
}

void CollisionOBB::SetRotation(glm::vec4 r)
{
	rotation = glm::eulerAngleYXZ(glm::radians(r.y), glm::radians(r.x), glm::radians(r.z));
}
