#include "pch.h"

ServiceLocator* ServiceLocator::instance = nullptr;
ServiceLocator* ServiceLocator::GetInstance()
{
	static ServiceLocator* instance = new ServiceLocator();
	return instance;
}
ServiceLocator::~ServiceLocator()
{
	delete instance;
}

FrameRateController* ServiceLocator::Services::GetFrameRateController()
{
	return frameRateController;
}

EventSystem* ServiceLocator::Services::GetEventSystem()
{
	return eventSystem;
}

InputManager* ServiceLocator::Services::GetInputManager()
{
	return inputManager;
}

ResourceManager* ServiceLocator::Services::GetResourceManager()
{
	return resourceManager;
}

ObjectFactory* ServiceLocator::Services::GetObjectFactory()
{
	return objectFactory;
}

Renderer* ServiceLocator::Services::GetRenderer()
{
	return renderer;
}

PhysicsManager* ServiceLocator::Services::GetPhysicManager()
{
	return physicManager;
}
