#pragma once

//class Component; // Forward declaration
class GameObject : public Node
{

public:

	GameObject();
	GameObject(Transform t, Mesh m, Material* mat);
	~GameObject();

	virtual void Init();
	virtual void Update();
	virtual void Destroy();
	//virtual void HandleEvent(void* eventData);
	virtual void Draw();

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

	void SetMaterial(Material* m);
	void SetMesh(Mesh* m);
	Material* GetMaterial();

	bool CheckIsAlive();
	void SetAlive(bool b);
	void SetToBeDeleted();

private:

	std::vector<Component*> components;
	bool isAlive = true;
	bool setDeleted = false;
};

