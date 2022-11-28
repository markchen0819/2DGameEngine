#include "pch.h"
#include <random>


void EnemyComponent::Init()
{
	tc = GetOwner()->GetComponent<TransformComponent>();
	pc = GetOwner()->GetComponent<PhysicComponent>();

	// random float between -1 to 1

	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(-1, 1);

	xdir = dis(gen);
	ydir = dis(gen);
}
void EnemyComponent::Update()
{
	float deltaTime = FrameRateController::GetInstance()->DeltaTime();
	int sign = 5;
	if (ydir < 0) sign = -5;
	tc->SetRotation(0, 0, tc->GetRotation().z + sign * speed *  deltaTime);
	pc->SetVelocity(glm::vec3(xdir * speed * deltaTime, ydir * speed* deltaTime, 0));


	float xoffset = xdir * speed * deltaTime;
	float yoffset = ydir * speed * deltaTime;

	// Boundaries
	if (pc->GetPosition().x > boundaries)
	{
		xdir = -xdir;
		tc->SetTranslation(boundaries - xoffset, pc->GetPosition().y, pc->GetPosition().z);
		WaveEvent w("WaveR");
		EventSystem::GetInstance()->BroadcastEvent(EventType::Wave, &w);
	}
	if (pc->GetPosition().x < -boundaries)
	{
		xdir = -xdir;
		tc->SetTranslation(-boundaries - xoffset, pc->GetPosition().y, pc->GetPosition().z);
		WaveEvent w("WaveL");
		EventSystem::GetInstance()->BroadcastEvent(EventType::Wave, &w);
	}
	if (pc->GetPosition().y > boundaries)
	{
		ydir = -ydir;
		tc->SetTranslation(pc->GetPosition().x, boundaries- yoffset, pc->GetPosition().z);
		WaveEvent w("WaveU");
		EventSystem::GetInstance()->BroadcastEvent(EventType::Wave, &w);
	}
	if (pc->GetPosition().y < -boundaries)
	{
		ydir = -ydir;
		tc->SetTranslation(pc->GetPosition().x, -boundaries - yoffset, pc->GetPosition().z);
		WaveEvent w("WaveD");
		EventSystem::GetInstance()->BroadcastEvent(EventType::Wave, &w);
	}
}
void EnemyComponent::Destroy()
{
	TraceMessage("Destroy EnemyComponent");
}