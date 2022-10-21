#pragma once
#include "Graphics/Node.h"
#include "Physics/Body.h"

class GameObject // Inherit from Node
{

public:

	GameObject();
	~GameObject();

	std::string Name = ""; // Just for identifying purpose
	Node* node = nullptr;
	Body* body = nullptr;

    void Draw();
	void AttachNode(Node* n);
	void AttachBody(Body* b);
	void SetBodyCollisionShape(CollisionShape* cs);


private:


};

