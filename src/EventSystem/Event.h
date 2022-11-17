#pragma once

class Event
{
public:
	Event() {};
	~Event() {};
};


class GameObject;
class CollisionEvent : public Event
{
public:
	CollisionEvent(GameObject* g1, GameObject* g2) :
		gobj1(g1), gobj2(g2)
	{};
	~CollisionEvent() {};

	GameObject* gobj1;
	GameObject* gobj2;
};

class Scene;
class SceneChangeEvent : public Event
{
public:
	SceneChangeEvent(Scene* scene): nextScene(scene){};
	~SceneChangeEvent() {};

	Scene* nextScene;
};