#include "pch.h"
GameEngine* GameEngine::instance = nullptr;
GameEngine* GameEngine::GetInstance()
{
	static GameEngine* instance = new GameEngine();
	return instance;
}
GameEngine::~GameEngine()
{
	delete instance;
}

// declaration for event registering
void CollisionCallback(void* eventData); 
void SceneChangeCallback(void* eventData);

void GameEngine::Initialize()
{
	TraceMessage("---------------------");
	TraceMessage(" GameEngine::Initialize()");
	TraceMessage("---------------------");

	serviceLocator = ServiceLocator::GetInstance();
	serviceLocator->EngineServices.GetRenderer()->InitGLFW();

	mainWindow = new GameWindow();
	mainWindow->Props.Title = "1stWindow";
	mainWindow->Init();
	mainWindow->SetWindowPosition(0, 50);
	// Experimenting 2nd window
	//GameWindow* secondWindow = new GameWindow();
	//secondWindow->Props.Title = "2ndWindow";
	//secondWindow->Init();

	serviceLocator->EngineServices.GetFrameRateController()->SetTargetFrameRate(60.0);
	serviceLocator->EngineServices.GetInputManager()->Init(mainWindow);

	// Regiseter Engine Events
	EventSystem* eventSystem = serviceLocator->EngineServices.GetEventSystem();
	sceneChangeEventLister.SetCallback(SceneChangeCallback);
	sceneChangeEventLister.SetType(EventType::SceneChange);
	eventSystem->AddListener(EventType::SceneChange, &sceneChangeEventLister);
	collisionEventLister.SetCallback(CollisionCallback);
	collisionEventLister.SetType(EventType::Collision);
	eventSystem->AddListener(EventType::Collision, &collisionEventLister);

	isRunning = true;
}

void GameEngine::Quit()  // Destroy everything (engine itself, stack of scenes, windows)
{
	TraceMessage("---------------------");
	TraceMessage(" GameEngine::Quit() ");
	TraceMessage("---------------------");
	serviceLocator->EngineServices.GetEventSystem()->RemoveAllListeners();
	while (!scenesStack.empty())
	{ 
		scenesStack.top()->Destroy();
		scenesStack.pop(); 
	}
	mainWindow->ShutDown();
	delete mainWindow;
	serviceLocator->EngineServices.GetRenderer()->TerminateGLFW();
}


void GameEngine::SetAllScenes(std::vector<Scene*>& scenes)
{
	TraceMessage("---------------------");
	TraceMessage("GameEngine::SetAllScenes (Game Levels) ");
	TraceMessage("---------------------");

	for (Scene* s : scenes)
	{
		TraceMessage((*s).Name.c_str());
	}
	AllScenes = scenes;
}

void GameEngine::ChangeScene(Scene* scene)
{
	TraceMessage("---------------------");
	TraceMessage(("GameEngine::ChangeScene: "+ (*scene).Name).c_str());
	TraceMessage("---------------------");
	if (!scenesStack.empty())
	{
		// Clears memory of current scene
		scenesStack.top()->Destroy(); 
		scenesStack.pop();
	}
	// Load Memory of new scene
	(*scene).Init(GetMainWindow()); 
	scenesStack.push(scene);
}

void GameEngine::PushScene(Scene* scene)
{
	TraceMessage("---------------------");
	TraceMessage(("GameEngine::PushScene: " + (*scene).Name).c_str());
	TraceMessage("---------------------");
	if (!scenesStack.empty())
	{
		scenesStack.top()->Pause();
	}
	scenesStack.push(scene);
}

void GameEngine::PopScene()
{
	TraceMessage("---------------------");
	TraceMessage(" GameEngine::PopScene()");
	TraceMessage("---------------------");
	if (!scenesStack.empty())
	{
		scenesStack.top()->Destroy();
		scenesStack.pop();
		scenesStack.top()->Resume();
	}
}

void GameEngine::Update()
{
	serviceLocator->EngineServices.GetFrameRateController()->FrameStart();
	mainWindow->Update();
	serviceLocator->EngineServices.GetRenderer()->ClearScreen();
	scenesStack.top()->Update();
}

void GameEngine::Draw()
{
	scenesStack.top()->Draw();
}

void GameEngine::PostUpdate()
{
	scenesStack.top()->LateUpdate();
	mainWindow->SwapBuffers();
	mainWindow->PollEvents();
	serviceLocator->EngineServices.GetInputManager()->PollEvents();
	serviceLocator->EngineServices.GetFrameRateController()->FrameEnd();
}

bool GameEngine::IsRunning()
{
	if (mainWindow->ShouldClose())
	{
		isRunning = false;
	}
	return isRunning;
}



GameWindow* GameEngine::GetMainWindow()
{
	return mainWindow;
}


// Event Callbacks for engine
void CollisionCallback(void* eventData)
{
	CollisionEvent* converted = static_cast<CollisionEvent*>(eventData);
	if (converted)
	{
		std::cout << "TimeStamp: " << glfwGetTime() << std::endl;
		std::cout << "Collision between " << converted->gobj1->GetName()
			<< " and " << converted->gobj2->GetName() << std::endl;

		if (converted->gobj1->GetName() != "Player")
		{
			converted->gobj1->SetAlive(false);
			converted->gobj1->SetToBeDeleted();
		}
		if (converted->gobj2->GetName() != "Player")
		{
			converted->gobj2->SetAlive(false);
			converted->gobj2->SetToBeDeleted();
		}
	}

}

void SceneChangeCallback(void* eventData)
{
	SceneChangeEvent* converted = static_cast<SceneChangeEvent*>(eventData);
	if (converted)
	{
	}
}