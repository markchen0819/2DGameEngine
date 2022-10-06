#pragma once
#include "Transform.h"
#include "Mesh.h"
class GameObject // Inherit from Node
{

public:

	GameObject(Transform t, Mesh m);
	~GameObject();

	Transform transform;
	Mesh mesh;

    void Draw(glm::mat4 model, Shader& shader);

private:


};

