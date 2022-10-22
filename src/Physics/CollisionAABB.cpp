#include "CollisionAABB.h"

CollisionAABB::CollisionAABB()
{
	Type = ShapeType::AABB;
	Right = 5.0f;
	Up = 5.0f;
	Left = -5.0f;
	Down = -5.0f;
}
CollisionAABB::CollisionAABB(float r, float l, float u, float d):Right(r),Down(d),Left(l),Up(u)
{
	Type = ShapeType::AABB;
}

CollisionAABB::~CollisionAABB()
{
}
