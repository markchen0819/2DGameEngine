#include "pch.h"

PhysicComponent::PhysicComponent(){}
PhysicComponent::~PhysicComponent() {}

void PhysicComponent::SetTranslation(glm::vec3 p) { physicBody->Position = p; }
void PhysicComponent::SetRotation(glm::vec3 r) { physicBody->Rotation = r; }
//void PhysicComponent::SetScale(glm::vec3 s) { physicBody->Scale = s; }
glm::vec3 PhysicComponent::GetPosition() { return physicBody->Position; }
glm::vec3 PhysicComponent::GetScale() { return physicBody->Scale; }
glm::vec3 PhysicComponent::GetRotation() { return physicBody->Rotation; }
void PhysicComponent::SetVelocity(glm::vec3 v){ physicBody->Velocity = v; }
void PhysicComponent::SetAcceleration(glm::vec3 a) { physicBody->Acceleration = a; }
void PhysicComponent::SetForce(glm::vec3 f) { physicBody->Force = f; }
void PhysicComponent::SetAngularVelocity(glm::vec3 av) { physicBody->AngularVelocity = av; }
void PhysicComponent::SetMass(float m) { physicBody->Mass = m; }
void PhysicComponent::SetInverseMass(float im) { physicBody->InverseMass = im; }


void PhysicComponent::Init() 
{ 
	physicBody = PhysicsManager::GetInstance()->CreateBody();
	// Init collision shape
	std::vector<glm::vec4> obbVerticies;
	obbVerticies.push_back(glm::vec4(100.0f, 100.0f, 0.0f, 1.0f));
	obbVerticies.push_back(glm::vec4(100.0f, -100.0f, 0.0f, 1.0f));
	obbVerticies.push_back(glm::vec4(-100.0f, -100.0f, 0.0f, 1.0f));
	obbVerticies.push_back(glm::vec4(-100.0f, 100.0f, 0.0f, 1.0f));
	CollisionOBB* obb = new CollisionOBB(obbVerticies);
	physicBody->SetCollisionShape(obb);
	physicBody->GetCollisionAreaObject().SetMesh(obbVerticies); // Debug

	// Init transform
	Transform* trans = GetOwner()->transform;
	physicBody->SetTransform(trans);
	physicBody->Position = trans->GetPosition();
	physicBody->Rotation = trans->GetRotation();
	physicBody->Scale = trans->GetScale();
}
void PhysicComponent::Update() 
{
	if (ShowCollisionArea)
	{
		physicBody->GetCollisionAreaObject().Draw();
	}
}
void PhysicComponent::Destroy() 
{
	delete physicBody;
}
//void PhysicComponent::HandleEvent(void* eventData){}


void PhysicComponent::Integrate()
{
	physicBody->Integrate();
}
Body* PhysicComponent::GetBody()
{
	return physicBody;
}
CollisionAreaObject& PhysicComponent::GetCollisionAreaObject()
{
	return physicBody->GetCollisionAreaObject();
}
