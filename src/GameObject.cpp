#include "pch.h"

GameObject::GameObject() { }
GameObject::~GameObject() {}

void GameObject::Init() 
{
	if (!isAlive) return;

	std::vector<Component*>::iterator it = components.begin();
	while (it != components.end())
	{
		if (!*it)
		{
			TraceMessage("Error: Init NULL component");
		}
		(*it)->Init();
		it = it + 1;
	}
	Node::Init();

}
void GameObject::Update() 
{
	if (setDeleted)
	{
		ObjectFactory::GetInstance()->AddForDeletion(this);
	}

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
	Node::Update();
}
void GameObject::Destroy() 
{
	TraceMessage(("Destroy GameObject: "+ Name).c_str());
	std::vector<Component*>::iterator it = components.begin();
	while (it != components.end())
	{
		if (!*it)
		{
			TraceMessage("Error: Deleting non existed component");
		}
		(*it)->Destroy();
		delete (*it);
		it = it + 1;
	}
	components.clear();
	Node::Destroy();
}
//void GameObject::HandleEvent(void* eventData) 
//{
//	std::vector<Component*>::iterator it = components.begin();
//	while (it != components.end())
//	{
//		if (!*it)
//		{
//			TraceMessage("Error: HandleEvent of non existed component");
//		}
//		(*it)->HandleEvent(eventData);
//		it = it + 1;
//	}
//	components.clear();
//	Node::HandleEvent(eventData);
//}

void GameObject::Draw()
{
	if (!isAlive) return;

	RenderComponent* renderComponent = this->GetComponent<RenderComponent>();
	if(!renderComponent)
	{
		return; //Don't draw
	}
	renderComponent->Draw();
	Node::Draw();
}

void GameObject::SetMaterial(Material* m)
{
	material = m;
}

Material* GameObject::GetMaterial()
{
	return material;
}


bool GameObject::CheckIsAlive()
{
	return isAlive;
}

void GameObject::SetAlive(bool b)
{
	isAlive = b;
}

void GameObject::SetToBeDeleted()
{
	setDeleted = true;
}
