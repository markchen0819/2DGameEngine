#pragma once
#include "Component.h"
#include "../Graphics/Mesh.h"
#include "../Graphics/Material.h"

class RenderComponent : public Component
{
public:
	RenderComponent();
	~RenderComponent();

	//template <class T>
	//void SetMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
	//{
	//	Mesh* mesh = new T;
	//	mesh.loadVertices();
	//	GetOwner()->SetMesh(mesh);
	//}

	virtual void Init();
	virtual void Update();
	virtual void Destroy();
	virtual void HandleEvent(void* eventData);

	void Draw();

	void SetMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	Mesh* GetMesh();
	Material* GetMaterial();

private:
	
};

