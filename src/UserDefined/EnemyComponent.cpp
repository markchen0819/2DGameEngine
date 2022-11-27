#include "pch.h"


void EnemyComponent::Init()
{
	tc = GetOwner()->GetComponent<TransformComponent>();
	pc = GetOwner()->GetComponent<PhysicComponent>();

	// random float between -1 to 1
	xdir = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - (-1))));
	ydir = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - (-1))));
}
void EnemyComponent::Update()
{
	float deltaTime = FrameRateController::GetInstance()->DeltaTime();
	tc->SetRotation(0, 0, tc->GetRotation().z + ydir * speed * 50 *  deltaTime);
	pc->SetVelocity(glm::vec3(xdir * speed * deltaTime, ydir * speed* deltaTime, 0));


	float xoffset = xdir * speed * deltaTime;
	float yoffset = ydir * speed * deltaTime;

	// Boundaries
	if (pc->GetPosition().x > boundaries)
	{
		xdir = -xdir;
		tc->SetTranslation(boundaries - xoffset, pc->GetPosition().y, pc->GetPosition().z);
	}
	if (pc->GetPosition().x < -boundaries)
	{
		xdir = -xdir;
		tc->SetTranslation(-boundaries - xoffset, pc->GetPosition().y, pc->GetPosition().z);
	}
	if (pc->GetPosition().y > boundaries)
	{
		ydir = -ydir;
		tc->SetTranslation(pc->GetPosition().x, boundaries- yoffset, pc->GetPosition().z);
	}
	if (pc->GetPosition().y < -boundaries)
	{
		ydir = -ydir;
		tc->SetTranslation(pc->GetPosition().x, -boundaries - yoffset, pc->GetPosition().z);
	}
}
void EnemyComponent::Destroy()
{
	TraceMessage("Destroy EnemyComponent");
}