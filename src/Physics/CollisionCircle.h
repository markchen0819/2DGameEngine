#pragma once
#include "CollisionShape.h"

class CollisionCircle : public CollisionShape
{
public:
	CollisionCircle();
	CollisionCircle(float r);
	~CollisionCircle();
	float Radius;
};

