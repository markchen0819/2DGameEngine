#include "../Allheaders.h"


RenderComponent::RenderComponent() { }

RenderComponent::~RenderComponent() { }

void RenderComponent::Draw()
{

}

void RenderComponent::SetMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
	Mesh* m = GetOwner()->mesh;
	m->DeleteMesh();
	m->SetVerticesAndIndicies(vertices, indices);
	m->CreateMeshFromData();
}

Mesh* RenderComponent::GetMesh()
{
	return GetOwner()->mesh;
}

Material* RenderComponent::GetMaterial()
{
	return GetOwner()->GetMaterial();
}

void RenderComponent::Init() { }
void RenderComponent::Update() 
{
	GetOwner()->UpdateModelMatrix();
	GetOwner()->Draw();
}
void RenderComponent::Destroy() {}
void RenderComponent::HandleEvent(void* eventData) {}