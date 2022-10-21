#pragma once
#include "ShapeType.h"
#include "../Debug/CollisionAreaObject.h"


class CollisionShape
{
public:
	ShapeType Type;
	CollisionShape();
	~CollisionShape();

	// Debug only
	CollisionAreaObject* collisionAreaObject = nullptr;
};

