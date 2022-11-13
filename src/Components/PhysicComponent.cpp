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
	// If not using Serialized values, use this default
	// else see PhysicComponent::Deserialize
	if (physicBody == nullptr)
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
	}
	// Init transform
	Transform* trans = GetOwner()->transform;
	physicBody->SetTransform(trans);
	physicBody->Position = trans->GetPosition();
	physicBody->Rotation = trans->GetRotation();
	physicBody->Scale = trans->GetScale();
}
void PhysicComponent::Update() { }
void PhysicComponent::Destroy() 
{
	std::string s = "Destroy PhysicComponent";
	TraceMessage(s.c_str());
	delete physicBody;
}

//void PhysicComponent::HandleEvent(void* eventData){}


void PhysicComponent::Integrate()
{
	if (GetOwner()->CheckIsAlive())
	{
		physicBody->Integrate();
	}

}
Body* PhysicComponent::GetBody()
{
	return physicBody;
}

void PhysicComponent::Serialize()
{
}

void PhysicComponent::Deserialize(const rapidjson::Value& componentMembers)
{
	TraceMessage("PhysicComponent::Deserialize");
	physicBody = PhysicsManager::GetInstance()->CreateBody();

	auto va = componentMembers.FindMember(JSONConstants::VELOCITY)->value.GetArray();
	SetVelocity(glm::vec3(va[0].GetFloat(), va[1].GetFloat(), va[2].GetFloat()));
	auto aa = componentMembers.FindMember(JSONConstants::ACCELERATION)->value.GetArray();
	SetAcceleration(glm::vec3(aa[0].GetFloat(), aa[1].GetFloat(), aa[2].GetFloat()));
	auto fa = componentMembers.FindMember(JSONConstants::FORCE)->value.GetArray();
	SetForce(glm::vec3(fa[0].GetFloat(), fa[1].GetFloat(), fa[2].GetFloat()));
	auto ava = componentMembers.FindMember(JSONConstants::ANGULARVELOCITY)->value.GetArray();
	SetAngularVelocity(glm::vec3(ava[0].GetFloat(), ava[1].GetFloat(), ava[2].GetFloat()));
	int m = componentMembers.FindMember(JSONConstants::MASS)->value.GetInt();
	SetMass(m);
	int im = componentMembers.FindMember(JSONConstants::INVERSEMASS)->value.GetInt();
	SetInverseMass(im);
	
	std::string collisionShapeTypeStr = componentMembers.FindMember(JSONConstants::COLLISION_SHAPE_TYPE)->value.GetString();
	if (collisionShapeTypeStr == "AABB")
	{
		//TO:DO
	}
	else if (collisionShapeTypeStr == "CIRCLE")
	{
		//TO:DO
	}
	else if (collisionShapeTypeStr == "OBB")
	{
		// Init collision shape
		std::vector<glm::vec4> obbVertices;
		const rapidjson::Value& verticesArray = componentMembers.FindMember(JSONConstants::VERTICES)->value;
		for (rapidjson::SizeType i = 0; i < verticesArray.Size(); ++i)
		{
			const rapidjson::Value& vertice = verticesArray[i];
			glm::vec4 v = glm::vec4(vertice[0].GetFloat(), vertice[1].GetFloat(), vertice[2].GetFloat(), vertice[3].GetFloat());
			obbVertices.push_back(v);
		}
		CollisionOBB* obb = new CollisionOBB(obbVertices);
		physicBody->SetCollisionShape(obb);
		PhysicsManager::GetInstance()->collisionManager.AddGameObjectForCollisionChecking(GetOwner());
	}

}
