#pragma once

class Node
{
public:
	Node();
	Node(Transform t, Mesh m, Material* mat);
	virtual ~Node();

	virtual void Init(); 
	virtual void Update();
	virtual void Destroy();
	//virtual void HandleEvent(void* eventData);
	virtual void Draw();

	Node* GetParent();
	void AddChild(Node* node);

	std::string Name = "";
	Transform* transform = nullptr;
	Mesh* mesh = nullptr;
	Material* material = nullptr;

protected:
	Node* parent = nullptr;
	std::vector<Node*> childNodes;
};

