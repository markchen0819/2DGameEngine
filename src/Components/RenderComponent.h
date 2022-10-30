#pragma once
#include "../Graphics/Renderer.h"
#include "Component.h"

class RenderComponent : public Component
{
public:
	RenderComponent();
	~RenderComponent();

	virtual void Init();
	virtual void Update();
	virtual void Destroy();
	//virtual void HandleEvent(void* eventData);

	void Draw();
	void SetMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	Mesh* GetMesh();
	Material* GetMaterial();

private:

};

