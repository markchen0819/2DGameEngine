#pragma once
#include "CollisionManager.h"
class PhysicsManager
{
public:

	~PhysicsManager();
	static PhysicsManager* GetInstance();

	Body* CreateBody();
	void Integrate();

	CollisionManager collisionManager;

private:
	PhysicsManager() {}; 
	static PhysicsManager* instance;

	std::vector<Body*> allBodies; // keep track of Bodies Created

};

