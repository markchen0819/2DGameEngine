#pragma once
#include "CollisionShape.h"
#include "../EventSystem.h"
#include "../GameObject.h"

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();
	bool CheckCollision(CollisionShape* shape1, glm::vec3 center1, CollisionShape* shape2, glm::vec3 center2);

};





// Collision Event testing
class CollisionEvent : public Event
{
public:

	GameObject* gobj1 = nullptr;
	GameObject* gobj2 = nullptr;

	CollisionEvent()
	{ 
		Type = EventType::Collision; 
	};
	~CollisionEvent() {};

	void print() const
	{
		std::cout << "CollisionEvent!: " << (*gobj1).Name <<" & "<< (*gobj2).Name <<std::endl;
	}

};

class CollisionEventListener : public EventListener
{
public:
	CollisionEventListener() { Type = EventType::Collision; }
	~CollisionEventListener() {}

	virtual void HandleEvent(const Event& e)
	{
		if (e.Type == Type) // Default
		{
			const  CollisionEvent& c = static_cast<const CollisionEvent&>(e);
			c.print();
		}
	}
};
