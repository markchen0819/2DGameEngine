#pragma once
#include "CollisionShape.h"
#include "../Debug/CollisionAreaObject.h"

class CollisionCircle : public CollisionShape
{
public:
	CollisionCircle();
	CollisionCircle(float r);
	~CollisionCircle();
	float Radius;
};

