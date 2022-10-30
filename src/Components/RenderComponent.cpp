#include "RenderComponent.h"

RenderComponent::RenderComponent() { }
RenderComponent::~RenderComponent() { }

void RenderComponent::Init() { }
void RenderComponent::Update()
{
	Renderer::GetInstance()->UpdateModelMatrix(GetOwner()->GetParent(), GetOwner()->transform);
}
void RenderComponent::Destroy() { }
// void RenderComponent::HandleEvent(void* eventData) { }


void RenderComponent::Draw()
{
	Renderer::GetInstance()->Draw(GetOwner()->Name, GetOwner()->transform, GetMesh(), GetMaterial());
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
