#include "pch.h"

Body::Body() 
{
	collisionAreaObject = new CollisionAreaObject();
}
Body::~Body() 
{
	delete collisionAreaObject;
	if (collisionShape != nullptr)
	{
		delete collisionShape;
	}
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

	// Feed calculations from Physics to Graphics Node's Transform
	FeedPhysicsCalculationToTransform();

	// Reset
	Acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	Force = glm::vec3(0.0f, 0.0f, 0.0f);
	AngularVelocity = glm::vec3(0.0f, 0.0f, 0.0f);

	Velocity = glm::vec3(0.0f, 0.0f, 0.0f); // Put this here for convenience now
}
void Body::FeedPhysicsCalculationToTransform()
{
	// Feed Graphic Node Transform
	if (transform != nullptr)
	{
		transform->SetTranslation(Position.x, Position.y, Position.z);
		transform->SetRotation(Rotation.x, Rotation.y, Rotation.z);	
		transform->SetScale(Scale.x, Scale.y, Scale.z);

		// Debug View 
		collisionAreaObject->UpdateTransform(*transform);
	}
	else
	{
		TraceMessage("Body has NULL transform");
	}
	// Feed ColllisionShape Transform
	if (collisionShape != nullptr) 
	{
		collisionShape->SetScale(glm::vec3(Scale.x, Scale.y, Scale.z));

		if (collisionShape->Type == ShapeType::OBB)
		{
			CollisionOBB* obb = (CollisionOBB*)collisionShape;
			obb->SetCenter(glm::vec4(Position, 1.0f));
			obb->SetRotation(glm::vec4(Rotation, 1.0f));
		}
	}
	else
	{
		TraceMessage("Body has NULL collisionShape");
	}
}
void Body::SetCollisionShape(CollisionShape* cs)
{
	collisionShape = cs;
}
CollisionShape* Body::GetCollisionShape()
{
	return collisionShape;
}
void Body::SetTransform(Transform* t)
{
	transform = t;
}

// Debug only
void Body::PrintInfo()
{
	std::cout << "Position: " << glm::to_string(Position) << std::endl;
	std::cout << "Rotation: " << glm::to_string(Rotation) << std::endl;
	std::cout << "Scale: " << glm::to_string(Scale) << std::endl;
}
CollisionAreaObject& Body::GetCollisionAreaObject()
{
	return *collisionAreaObject;
}