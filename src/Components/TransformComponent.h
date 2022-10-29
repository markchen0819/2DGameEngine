#pragma once
#include "Component.h"
#include "../Graphics/Transform.h"

class TransformComponent : public Component
{
public:
	TransformComponent();
	~TransformComponent();

	void SetRotation(const float x, const float y, const float z);
	void SetScale(const float x, const float y, const float z);
	void SetTranslation(const float x, const float y, const float z);
	glm::vec3 GetPosition();
	glm::vec3 GetScale();
	glm::vec3 GetRotation();
	glm::mat4 GetRotationMatrix();
	glm::mat4 GetScaleMatrix();
	glm::mat4 GetTranlateMatrix();
	glm::mat4 getLocalModelMatrix();

	virtual void Init();
	virtual void Update();
	virtual void Destroy();
	virtual void HandleEvent(void* eventData);

private:
	
	Transform* transform;  // point to the gameobject's transform
};

