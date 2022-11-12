#include "pch.h"

TransformComponent::TransformComponent(){}
TransformComponent::~TransformComponent(){}

void TransformComponent::SetRotation(const float x, const float y, const float z)
{
	(*transform).SetRotation(x, y, z);
}
void TransformComponent::SetScale(const float x, const float y, const float z)
{
	(*transform).SetScale(x, y, z);
}
void TransformComponent::SetTranslation(const float x, const float y, const float z)
{
	(*transform).SetTranslation(x, y, z);
}
glm::vec3 TransformComponent::GetPosition()
{
	return (*transform).GetPosition();
}
glm::vec3 TransformComponent::GetScale()
{
	return (*transform).GetScale();
}
glm::vec3 TransformComponent::GetRotation()
{
	return (*transform).GetRotation();
}
glm::mat4 TransformComponent::GetRotationMatrix()
{
	return (*transform).GetRotationMatrix();
}
glm::mat4 TransformComponent::GetScaleMatrix()
{
	return (*transform).GetScaleMatrix();
}
glm::mat4 TransformComponent::GetTranlateMatrix()
{
	return (*transform).GetTranlateMatrix();
}
glm::mat4 TransformComponent::getLocalModelMatrix()
{
	return (*transform).getLocalModelMatrix();
}


void TransformComponent::Init()
{
	transform = GetOwner()->transform;
}
void TransformComponent::Update() {}
void TransformComponent::Destroy() 
{
	std::string s = "DestroyTransformComponent";
	TraceMessage(s.c_str());
}

// void TransformComponent::HandleEvent(void* eventData) {}

void TransformComponent::Serialize()
{

}
void TransformComponent::Deserialize(const rapidjson::Value& componentMembers)
{
	TraceMessage("TransformComponent::Deserialize");
	transform = GetOwner()->transform;
	auto positionArray = componentMembers.FindMember(JSONConstants::POSITION)->value.GetArray();
	SetTranslation(positionArray[0].GetFloat(), positionArray[1].GetFloat(), positionArray[2].GetFloat());
	auto rotationArray = componentMembers.FindMember(JSONConstants::ROTATION)->value.GetArray();
	SetRotation(rotationArray[0].GetFloat(), rotationArray[1].GetFloat(), rotationArray[2].GetFloat());
	auto scaleArray = componentMembers.FindMember(JSONConstants::SCALE)->value.GetArray();
	SetScale(scaleArray[0].GetFloat(), scaleArray[1].GetFloat(), scaleArray[2].GetFloat());
}