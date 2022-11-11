#pragma once

class Component
{
public:
	Component();
	virtual ~Component();

	virtual void Init() { }
	virtual void Update() {}
	virtual void Destroy() {}
	//virtual void HandleEvent(void* eventData) {}

	GameObject* GetOwner();
	void SetOwner(GameObject* gobj);

	virtual void Serialize() {};
	virtual void Deserialize(const rapidjson::Value& obj) {};

private:
	friend class GameObject;
	GameObject* owner = nullptr;

};

