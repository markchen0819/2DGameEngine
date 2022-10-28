#include "../Allheaders.h"


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
	transform = GetOwner()->GetTransform();
}
void TransformComponent::Update() {}
void TransformComponent::Destroy() {}
void TransformComponent::HandleEvent(void* eventData) {}
