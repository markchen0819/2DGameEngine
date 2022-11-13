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
	void RemoveChild(Node* node);

	Transform* transform = nullptr;
	Mesh* mesh = nullptr;
	Material* material = nullptr;

	void SetName(std::string name);
	std::string GetName();

protected:
	std::string Name = "";
	Node* parent = nullptr;
	std::vector<Node*> childNodes;
};

