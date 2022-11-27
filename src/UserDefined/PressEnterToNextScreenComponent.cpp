#include "pch.h"

void PressEnterToNextScreenComponent::Init()
{

}

void PressEnterToNextScreenComponent::Update()
{
	// Input
	InputManager* inputmanager = InputManager::GetInstance();

	if (inputmanager->IsKeyDown(ENTER))
	{
		SceneChangeEvent sce(sceneName);
		EventSystem::GetInstance()->BroadcastEvent(EventType::SceneChange, &sce);
	}

}
void PressEnterToNextScreenComponent::Destroy()
{
	TraceMessage("Destroy PressEnterToNextScreenComponent");
}

void PressEnterToNextScreenComponent::SetSceneName(std::string name)
{
	sceneName = name;
}
