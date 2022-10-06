#pragma once
#include "Transform.h"
#include "Mesh.h"

class Node
{
public:

	Node(Transform t, Mesh m, Shader& s, glm::vec4 color);
	~Node();

	Transform transform;
	Mesh mesh;
	Shader shader;
	glm::vec4 color;

	void Draw();

private:


};

