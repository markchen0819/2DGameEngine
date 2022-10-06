#pragma once
#include "Transform.h"
#include "Mesh.h"

class Node
{
public:

	Node(Transform& t, Mesh& m, Shader& s);
	~Node();

	Transform transform;
	Mesh mesh;
	Shader shader;

	void Draw();

private:


};

