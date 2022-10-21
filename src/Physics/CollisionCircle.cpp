#include "CollisionCircle.h"
#include <GLEW/include/glew.h>

CollisionCircle::CollisionCircle()
{
	Type = ShapeType::CIRCLE;
	Radius = 0;
}

CollisionCircle::CollisionCircle(float r):Radius(r)
{
	Type = ShapeType::CIRCLE;
	collisionAreaObject = new CollisionAreaObject();
	collisionAreaObject->SetMesh(Radius);
}

CollisionCircle::~CollisionCircle()
{
	
}

