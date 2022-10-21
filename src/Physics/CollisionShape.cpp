#include "CollisionShape.h"

CollisionShape::CollisionShape()
{
	Type = ShapeType::NONE;
}
CollisionShape::~CollisionShape()
{
	if (collisionAreaObject != nullptr)
	{
		delete collisionAreaObject;
	}
}
