#include "pch.h"


void SelfRotateComponent::Init() 
{
	tc = GetOwner()->GetComponent<TransformComponent>();

}
void SelfRotateComponent::Update() 
{
	tc = GetOwner()->GetComponent<TransformComponent>(); // temp
	tc->SetRotation(0, 0, tc->GetRotation().z + 100 * FrameRateController::GetInstance()->DeltaTime());
}
void SelfRotateComponent::Destroy() 
{
	TraceMessage("Destroy SelfRotateComponen");
}