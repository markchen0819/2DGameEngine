#pragma once

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

	void Integrate();

	void SetCollisionShape(CollisionShape* cs);
	CollisionShape* GetCollisionShape();
	void SetTransform(Transform* t);

	// Debug only
	void PrintInfo();
	CollisionAreaObject& GetCollisionAreaObject();

private:

	CollisionShape* collisionShape = nullptr;
	Transform* transform = nullptr;
	void FeedPhysicsCalculationToTransform();

	// Debug only
	CollisionAreaObject* collisionAreaObject = nullptr;
};

