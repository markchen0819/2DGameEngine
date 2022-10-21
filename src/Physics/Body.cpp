#include "Body.h"
#include <glm/gtx/string_cast.hpp>

Body::Body() { }

Body::~Body() { }

void Body::AttachTransform(Transform* t)
{
	transform = t;
	Position = transform->GetPosition();
	Rotation = transform->GetRotation();
	Scale = transform->GetScale();
}

void Body::UpdateTransform()
{
	if (transform != nullptr)
	{
		transform->SetTranslation(Position.x, Position.y, Position.z);
		transform->SetRotation(Rotation.x, Rotation.y, Rotation.z);
		transform->SetScale(Scale.x, Scale.y, Scale.z);
	}
	collisionShape->collisionAreaObject->UpdateTransform(*transform);
}


void Body::Integrate()
{
	// Get current values
	Position = transform->GetPosition();
	Rotation = transform->GetRotation();
	Scale = transform->GetScale();

	// Calculate physics (per frame)
	Acceleration = Force * InverseMass;
	Velocity += Acceleration;
	Rotation += AngularVelocity;
	Position += Velocity;

	// Update values
	UpdateTransform();

	// Reset
	Acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	Force = glm::vec3(0.0f, 0.0f, 0.0f);
	AngularVelocity = glm::vec3(0.0f, 0.0f, 0.0f);

	Velocity = glm::vec3(0.0f, 0.0f, 0.0f); // Put this here for convenience now
}

void Body::PrintInfo()
{
	std::cout << "Position: " << glm::to_string(Position) << std::endl;
	std::cout << "Rotation: " << glm::to_string(Rotation) << std::endl;
	std::cout << "Scale: " << glm::to_string(Scale) << std::endl;
}
