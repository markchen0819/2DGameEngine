#pragma once
#include "Graphics/Node.h"
#include "Physics/Body.h"
#include "Logging.h"

class Component; // Forward declaration
class GameObject : public Node
{

public:

	GameObject();
	GameObject(const GameObject& obj);
	~GameObject();

	void Init();
	void Update();
	void Destroy();
	void HandleEvent(void* eventData);

	template<class T>
	void AddComponent()
	{
		T* component = new T;
		component->SetOwner(this);
		components.push_back(component);
	}


	template<class T>
	T* GetComponent()
	{
		std::vector<Component*>::iterator it = components.begin();
		while (it != components.end())
		{
			T* targetComponent = dynamic_cast<T*>((*it));
			if (targetComponent != 0)
			{
				return targetComponent;
			}
			it = it + 1;
		}
		TraceMessage("Null Component: ");
		TraceMessage(typeid(T).name());
		return nullptr;
	}


	//void Draw();
	Transform* GetTransform();
	void SetMaterial(Material* m);
	Material* GetMaterial();

	//void SetBodyCollisionShape(CollisionShape* cs);


private:

	std::vector<Component*> components;
	bool isAlive = true;
};

