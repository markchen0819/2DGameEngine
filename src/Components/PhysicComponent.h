#pragma once
#include "Component.h"
#include "../Physics/Body.h"
#include "../Physics/CollisionOBB.h"

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

	virtual void Init();
	virtual void Update();
	virtual void Destroy();
	//virtual void HandleEvent(void* eventData);

	void Integrate();
	Body* GetBody();

	//Debug
	bool ShowCollisionArea = true;
	CollisionAreaObject& GetCollisionAreaObject();

private:
	Body* physicBody = nullptr;
};

