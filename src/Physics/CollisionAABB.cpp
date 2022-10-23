#include "CollisionAABB.h"

CollisionAABB::CollisionAABB(): Right(10.0f), Up(10.0f), Left(-10.0f), Down(-10.0f)
{
	Type = ShapeType::AABB;
}
CollisionAABB::CollisionAABB(float r, float l, float u, float d):Right(r),Down(d),Left(l),Up(u)
{
	Type = ShapeType::AABB;
}
CollisionAABB::~CollisionAABB() { }
