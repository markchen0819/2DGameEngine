#include "pch.h"
#include <random>

void StarComponent::Init()
{
	tc = GetOwner()->GetComponent<TransformComponent>();
	pc = GetOwner()->GetComponent<PhysicComponent>();
	tc->SetScale(0.2, 0.2, 0.2);
	// random float between boundaries

	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> disx(-boundaries, boundaries);
	std::uniform_real_distribution<> disy(-boundaries, boundaries - 50);
	float x = disx(gen);
	float y = disy(gen);
	tc->SetTranslation(x, y, 0);
	TraceMessage(("Star generated at (" + std::to_string(x) + "," + std::to_string(y) + ")").c_str());
}

void StarComponent::Update()
{

}

void StarComponent::Destroy()
{
	TraceMessage("Destroy StarComponent");
}
