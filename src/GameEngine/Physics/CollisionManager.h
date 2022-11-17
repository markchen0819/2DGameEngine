#pragma once

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void AddGameObjectForCollisionChecking(GameObject* gobj);
	void RemoveGameObjectForCollisionChecking(GameObject* gobj);
	void CheckAllCollisions();
	bool CheckCollision(CollisionShape* shape1, glm::vec3 center1, CollisionShape* shape2, glm::vec3 center2);

private:
	std::vector<GameObject*> gobjList;
};

