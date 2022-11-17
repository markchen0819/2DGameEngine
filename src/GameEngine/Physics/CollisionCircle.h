#pragma once

class CollisionCircle : public CollisionShape
{
public:
	CollisionCircle();
	CollisionCircle(float r);
	~CollisionCircle();
	float Radius;
};

