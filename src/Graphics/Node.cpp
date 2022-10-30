#include "../pch.h"

Node::Node():transform(new Transform()), mesh(new Mesh()) {}
Node::Node(Transform t, Mesh m, Material* mat)
{
	transform = new Transform(t);
	mesh = new Mesh(m);
	material = mat;
}
Node::~Node()
{
	if (transform)
	{
		delete transform;
	}
	if (mesh)
	{
		delete mesh;
	}

	childNodes.clear();
}

void Node::Init()
{
	for (Node* n : childNodes)
	{
		n->Init();
	}
}
void Node::Update()
{
	// Render ability now belongs to RenderComponent
	// Renderer::GetInstance()->UpdateModelMatrix(parent, transform);
	for (Node* n : childNodes)
	{
		n->Update();
	}
}
void Node::Destroy()
{
	for (Node* n : childNodes)
	{
		n->Destroy();
	}
}
//void Node::HandleEvent(void* eventData){ }
void Node::Draw()
{
	// Render ability now belongs to RenderComponent
	// Renderer::GetInstance()->Draw(Name, transform, mesh, material);
	for (Node* n : childNodes)
	{
		n->Draw();
	}
}

Node* Node::GetParent()
{
	return parent;
}
void Node::AddChild(Node* node)
{
	node->parent = this;
	childNodes.push_back(node);
}

