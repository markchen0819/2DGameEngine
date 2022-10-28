#include "Allheaders.h"

GameObject::GameObject() { }
GameObject::~GameObject() { }

void GameObject::Init() { }
void GameObject::Update() 
{
	if (!isAlive) return;

	std::vector<Component*>::iterator it = components.begin();
	while (it != components.end())
	{
		if (!*it)
		{
			TraceMessage("Error: Updating NULL component");
		}
		(*it)->Update();
		it = it + 1;
	}
}
void GameObject::Destroy() 
{
	std::vector<Component*>::iterator it = components.begin();
	while (it != components.end())
	{
		if (!*it)
		{
			TraceMessage("Error: Deleting non existed component");
		}
		delete (*it);
		it = it + 1;
	}
	components.clear();
}
void GameObject::HandleEvent(void* eventData) {}

void GameObject::Draw()
{
	RenderComponent* renderComponent = this->GetComponent<RenderComponent>();
	if(!renderComponent)
	{
		return; //Don't draw
	}
	renderComponent->Draw();
	Node::Draw();
}

Transform* GameObject::GetTransform()
{
	return transform;
}

void GameObject::SetMaterial(Material* m)
{
	material = m;
}

Material* GameObject::GetMaterial()
{
	return material;
}


void GameObject::AddComponent(Component* component)
{
	component->SetOwner(this);
	components.push_back(component);
}

//void GameObject::SetBodyCollisionShape(CollisionShape * cs)
//{
//	body->collisionShape = cs;
//}
