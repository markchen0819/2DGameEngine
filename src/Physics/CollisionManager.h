#pragma once
#include "CollisionShape.h"
#include "../EventSystem/EventType.h"
#include "../EventSystem/EventSystem.h"
#include "../GameObject.h"

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void AddGameObjectForCollisionChecking(GameObject* gobj);
	void CheckAllCollisions();
	bool CheckCollision(CollisionShape* shape1, glm::vec3 center1, CollisionShape* shape2, glm::vec3 center2);

private:
	std::vector<GameObject*> gobjList;
};

