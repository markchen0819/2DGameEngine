#include "CollisionCircle.h"

CollisionCircle::CollisionCircle() : Radius(10)
{
	Type = ShapeType::CIRCLE;
}
CollisionCircle::CollisionCircle(float r):Radius(r)
{
	Type = ShapeType::CIRCLE;
}
CollisionCircle::~CollisionCircle() { }

