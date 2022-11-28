#include "pch.h"

void WaveComponent::Init()
{
}

void WaveComponent::Update()
{
	float deltaTime = FrameRateController::GetInstance()->DeltaTime();
	timer += deltaTime;

	if (timer > timeLimit)
	{
		ResetTimer();
		GetOwner()->SetAlive(false);
	}

}

void WaveComponent::Destroy()
{
	TraceMessage("Wave StarComponent");
}

void WaveComponent::ResetTimer()
{
	timer = 0;
}
