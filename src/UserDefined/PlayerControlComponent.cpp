#include "pch.h"

void PlayerControlComponent::Init()
{
	tc = GetOwner()->GetComponent<TransformComponent>();
	pc = GetOwner()->GetComponent<PhysicComponent>();
}
void PlayerControlComponent::Update()
{
	// Input
	InputManager* inputmanager = InputManager::GetInstance();

	float amount = 3 * 100 * FrameRateController::GetInstance()->DeltaTime();
	if (inputmanager->IsKeyDown(RIGHT))
	{
		pc->SetAngularVelocity(glm::vec3(0.0f, 0.0f, -amount));
	}
	if (inputmanager->IsKeyDown(LEFT))
	{
		pc->SetAngularVelocity(glm::vec3(0.0f, 0.0f, amount));
	}
	if (inputmanager->IsKeyDown(UP))
	{
		pc->SetVelocity(glm::vec3(tc->GetRotationMatrix() * glm::vec4(0.0f, amount, 0.0f, 1.0f)));
	}
	if (inputmanager->IsKeyDown(DOWN))
	{
		pc->SetVelocity(glm::vec3(tc->GetRotationMatrix() * glm::vec4(0.0f, -amount, 0.0f, 1.0f)));
	}
}
void PlayerControlComponent::Destroy() 
{
	TraceMessage("Destroy Player ControlComponent");
}