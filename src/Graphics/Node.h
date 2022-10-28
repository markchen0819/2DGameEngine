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

	void Draw();
	void UpdateModelMatrix();

	void AddChild(Node* node);

	std::string Name = "";
	Transform* transform = nullptr;
	Mesh* mesh = nullptr;
	Material* material = nullptr;

protected:

	Node* parent = nullptr;
	std::vector<Node*> childNodes;

};

