#pragma once
#include <glm/ext/vector_float3.hpp>
#include "../Graphics/Transform.h"
#include "../Physics/CollisionShape.h"
#include "../Debug/CollisionAreaObject.h"

class Body
{
public:

	Body();
	~Body();

	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Force = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 AngularVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
	float Mass = 1;
	float InverseMass = 1;

	Transform* transform = nullptr;
	CollisionShape* collisionShape = nullptr;

	void AttachTransform(Transform* t);
	void UpdateTransform();
	void Integrate();

	void PrintInfo();
	// Debug only
	CollisionAreaObject& GetCollisionAreaObject();

private:

	// Debug only
	CollisionAreaObject* collisionAreaObject = nullptr;
};

