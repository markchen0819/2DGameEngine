#pragma once
class ServiceLocator
{
	struct Services
	{
	public:
		FrameRateController* GetFrameRateController();
		EventSystem* GetEventSystem();
		InputManager* GetInputManager();
		ResourceManager* GetResourceManager();
		ObjectFactory* GetObjectFactory();
		Renderer* GetRenderer();
		PhysicsManager* GetPhysicManager();
	private:
		FrameRateController* frameRateController = FrameRateController::GetInstance();
		EventSystem* eventSystem = EventSystem::GetInstance();
		InputManager* inputManager = InputManager::GetInstance();
		ResourceManager* resourceManager = ResourceManager::GetInstance();
		ObjectFactory* objectFactory = ObjectFactory::GetInstance();
		Renderer* renderer = Renderer::GetInstance();
		PhysicsManager* physicManager = PhysicsManager::GetInstance();
	};

public:
	~ServiceLocator();
	static ServiceLocator* GetInstance();
	Services EngineServices;

private:
	ServiceLocator() {};
	static ServiceLocator* instance;
};