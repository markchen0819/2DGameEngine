#include "pch.h"

RenderComponent::RenderComponent() { }
RenderComponent::~RenderComponent() { }

void RenderComponent::Init() { }
void RenderComponent::Update()
{
	Renderer::GetInstance()->UpdateModelMatrix(GetOwner()->GetParent(), GetOwner()->transform);
}
void RenderComponent::Destroy() 
{
	std::string s = "DestroyRenderComponentt";
	TraceMessage(s.c_str());
}
// void RenderComponent::HandleEvent(void* eventData) { }


void RenderComponent::Draw()
{
	Renderer::GetInstance()->Draw(GetOwner()->GetName(), GetOwner()->transform, GetMesh(), GetMaterial());
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


void RenderComponent::Serialize()
{

}
void RenderComponent::Deserialize(const rapidjson::Value& componentMembers)
{
	TraceMessage("RenderComponent::Deserialize");
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	const rapidjson::Value& verticesArray = componentMembers.FindMember(JSONConstants::VERTICES)->value;
	for (rapidjson::SizeType i = 0; i < verticesArray.Size(); ++i)
	{
		const rapidjson::Value& vertice = verticesArray[i];
		glm::vec3 Position = glm::vec3(vertice[0].GetFloat(), vertice[1].GetFloat(), vertice[2].GetFloat());
		glm::vec3 Normal = glm::vec3(vertice[3].GetFloat(), vertice[4].GetFloat(), vertice[5].GetFloat());
		glm::vec2 TexCoords = glm::vec2(vertice[6].GetFloat(), vertice[7].GetFloat());
		Vertex v(Position, Normal, TexCoords);
		vertices.push_back(v);
	}
	auto indicesArray = componentMembers.FindMember(JSONConstants::INDICES)->value.GetArray();
	for (rapidjson::Value::ConstValueIterator itr = indicesArray.Begin(); itr != indicesArray.End(); ++itr)
	{
		indices.push_back(itr->GetFloat());
	}
	SetMesh(vertices, indices);
}