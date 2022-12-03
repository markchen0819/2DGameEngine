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

	float amount = 500 * FrameRateController::GetInstance()->DeltaTime();
	float diagonalAmount = amount / 1.414;


	 if (inputmanager->IsKeyDown(RIGHT) && inputmanager->IsKeyDown(UP))
	 {
		pc->SetVelocity(glm::vec3(diagonalAmount, diagonalAmount, 0.0f));
		tc->SetRotation(0, 0, -45);
	 }
	 else if (inputmanager->IsKeyDown(RIGHT) && inputmanager->IsKeyDown(DOWN))
	 {
		 pc->SetVelocity(glm::vec3(diagonalAmount, -diagonalAmount, 0.0f));
		 tc->SetRotation(0, 0, -135);
	 }
	 else if (inputmanager->IsKeyDown(LEFT) && inputmanager->IsKeyDown(UP))
	 {
		 pc->SetVelocity(glm::vec3(-diagonalAmount, diagonalAmount, 0.0f));
		 tc->SetRotation(0, 0, 45);
	 }
	 else if (inputmanager->IsKeyDown(LEFT) && inputmanager->IsKeyDown(DOWN))
	 {
		 pc->SetVelocity(glm::vec3(-diagonalAmount, -diagonalAmount, 0.0f));
		 tc->SetRotation(0, 0, 135);
	 }
	 else if (inputmanager->IsKeyDown(RIGHT))
	 {
		 pc->SetVelocity(glm::vec3(amount, 0.0f, 0.0f));
		 tc->SetRotation(0, 0, -90);
	 }
	 else if (inputmanager->IsKeyDown(LEFT))
	 {
		 pc->SetVelocity(glm::vec3(-amount, 0.0f, 0.0f));
		 tc->SetRotation(0, 0, 90);
	 }
	 else if (inputmanager->IsKeyDown(DOWN))
	 {
		 pc->SetVelocity(glm::vec3( 0.0f, -amount, 0.0f));
		 tc->SetRotation(0, 0, 180);
	 }
	 else if (inputmanager->IsKeyDown(UP))
	 {
		 pc->SetVelocity(glm::vec3(0.0f, amount, 0.0f));
		 tc->SetRotation(0, 0, 0);
	 }

	 // Boundaries
	 float boundaries = 280;

	 if (pc->GetPosition().x > boundaries)
	 {
		 tc->SetTranslation(boundaries, pc->GetPosition().y, pc->GetPosition().z);
	 } 
	 if (pc->GetPosition().x < -boundaries)
	 {
		 tc->SetTranslation(-boundaries, pc->GetPosition().y, pc->GetPosition().z);
	 }
	 if (pc->GetPosition().y > boundaries)
	 {
		 tc->SetTranslation(pc->GetPosition().x , boundaries, pc->GetPosition().z);
	 }
	 if (pc->GetPosition().y < -boundaries)
	 {
		 tc->SetTranslation(pc->GetPosition().x, -boundaries, pc->GetPosition().z);
	 }
	 if (pc->GetPosition().x > boundaries && pc->GetPosition().y > boundaries)
	 {
		 tc->SetTranslation(boundaries, boundaries, pc->GetPosition().z);
	 }
	 if (pc->GetPosition().x > boundaries && pc->GetPosition().y < -boundaries)
	 {
		 tc->SetTranslation(boundaries, -boundaries, pc->GetPosition().z);
	 }
	 if (pc->GetPosition().x < -boundaries && pc->GetPosition().y > boundaries)
	 {
		 tc->SetTranslation(-boundaries, boundaries, pc->GetPosition().z);
	 }
	 if (pc->GetPosition().x < -boundaries && pc->GetPosition().y < -boundaries)
	 {
		 tc->SetTranslation(-boundaries, -boundaries, pc->GetPosition().z);
	 }


}
void PlayerControlComponent::Destroy() 
{
	TraceMessage("Destroy Player ControlComponent");
}