#pragma once
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"

class Node
{
public:

	Node();
	Node(Transform t, Mesh m, Material* mat);
	~Node();

	Transform* transform = nullptr;
	Mesh* mesh = nullptr;
	Material* material = nullptr;

	void Draw();

	void AddChildNode(Node* node);

	Node* parent = nullptr;

private:
	std::vector<Node*> childNodes;
	void UpdateTransform();
};

