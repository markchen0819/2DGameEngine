#pragma once

class PhysicsManager
{
public:

	~PhysicsManager();
	static PhysicsManager* GetInstance();

	Body* CreateBody();
	void DeleteBody(Body* newBody);

	void Integrate();

	CollisionManager collisionManager;

private:
	PhysicsManager() {}; 
	static PhysicsManager* instance;

	std::vector<Body*> allBodies; // keep track of Bodies Created

};

