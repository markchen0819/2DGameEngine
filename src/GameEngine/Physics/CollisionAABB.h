#pragma once

class CollisionAABB : public CollisionShape
{
public:
	CollisionAABB();
	CollisionAABB(float r, float l, float u, float d);
	~CollisionAABB();
	float Right, Up, Left, Down;

private:
};

