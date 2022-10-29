#pragma once
#include <glm/ext/vector_float3.hpp>
#include "Component.h"
#include "../Physics/Body.h"

class PhysicComponent : public Component
{
public:
	PhysicComponent();
	~PhysicComponent();

	void SetTranslation(glm::vec3 p);
	void SetRotation(glm::vec3 r);
	//void SetScale(glm::vec3 s);
	glm::vec3 GetPosition();
	glm::vec3 GetScale();
	glm::vec3 GetRotation();

	void SetVelocity(glm::vec3 v);
	void SetAcceleration(glm::vec3 a);
	void SetForce(glm::vec3 f);
	void SetAngularVelocity(glm::vec3 av);
	void SetMass(float m);
	void SetInverseMass(float im);

	Body* GetBody();

	virtual void Init();
	virtual void Update();
	virtual void Destroy();
	virtual void HandleEvent(void* eventData);

	void Integrate();

	//Debug
	CollisionAreaObject& GetCollisionAreaObject();

private:

	Body* physicBody = nullptr;
	bool ShowCollisionArea = true;
};

