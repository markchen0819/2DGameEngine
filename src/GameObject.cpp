#include "GameObject.h"
#include "Graphics/Shader.h"

GameObject::GameObject()
{

}
GameObject::~GameObject()
{

}

void GameObject::Draw()
{
	node->Draw();
}

void GameObject::AttachNode(Node* n)
{
	node = n;
}

void GameObject::AttachBody(Body* b)
{
	body = b;
	body->transform = node->transform;
}

void GameObject::SetBodyCollisionShape(CollisionShape * cs)
{
	body->collisionShape = cs;
}
