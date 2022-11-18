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
	TraceInit();
	TraceMessage("--------------------------------");
	TraceMessage("GameEngine::Initialize()");
	TraceMessage("--------------------------------");

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
	TraceMessage("--------------------------------");
	TraceMessage("GameEngine::Quit() ");
	TraceMessage("--------------------------------");

	serviceLocator->EngineServices.GetEventSystem()->RemoveAllListeners();

	// Clear loaded memory by the scenes on the stack
	while (!scenesStack.empty())
	{ 
		scenesStack.top()->Destroy();
		scenesStack.pop(); 
	}
	// Clear memory of the scenes themselves
	DeleteAllScenes();

	mainWindow->ShutDown();
	delete mainWindow;
	serviceLocator->EngineServices.GetRenderer()->TerminateGLFW();
	TraceShutdown();
}


void GameEngine::SetAllScenes(std::vector<Scene*>& scenes)
{
	TraceMessage("--------------------------------");
	TraceMessage("GameEngine::SetAllScenes (Load in all user generated levels)");
	TraceMessage("--------------------------------");

	for (Scene* s : scenes)
	{
		TraceMessage((*s).Name.c_str());
	}
	AllScenes = scenes;
}

void GameEngine::DeleteAllScenes()
{
	TraceMessage("--------------------------------");
	TraceMessage("GameEngine::DeleteAllScenes (Delete all user generated levels) ");
	TraceMessage("--------------------------------");
	for (Scene* s : AllScenes)
	{
		delete s;
	}
}

void GameEngine::ChangeScene(Scene* scene)
{
	TraceMessage("--------------------------------");
	TraceMessage(("GameEngine::ChangeScene: "+ (*scene).Name).c_str());
	TraceMessage("--------------------------------");
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
	TraceMessage("--------------------------------");
	TraceMessage(("GameEngine::PushScene: " + (*scene).Name).c_str());
	TraceMessage("--------------------------------");
	if (!scenesStack.empty())
	{
		scenesStack.top()->Pause();
	}
	scenesStack.push(scene);
}

void GameEngine::PopScene()
{
	TraceMessage("--------------------------------");
	TraceMessage("GameEngine::PopScene()");
	TraceMessage("--------------------------------");
	if (!scenesStack.empty())
	{
		scenesStack.top()->Destroy();
		scenesStack.pop();
		scenesStack.top()->Resume();
	}
}

Scene* GameEngine::GetSceneByName(std::string sceneName)
{
	for (Scene* s : AllScenes)
	{
		if ((*s).Name == sceneName)
		{
			return s;
		}
	}
	TraceMessage(("Target Scene Not found: " + sceneName).c_str());
	return nullptr;
}

void GameEngine::AddSceneToChange(std::string sceneName)
{
	sceneToChange.push_back(sceneName);
}

void GameEngine::DeferredChangeScene() 
{
	for (std::string s : sceneToChange)
	{
		Scene* scene = GetSceneByName(s);
		if (scene != nullptr)
		{
			ChangeScene(scene);
		}
	}
	sceneToChange.clear();
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
	DeferredChangeScene();
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
		TraceMessage("CollisionEvent: ");
		std::string timeStr = std::to_string(glfwGetTime());
		TraceMessage(("TimeStamp: " + timeStr).c_str());
		std::string str = "Collision between " + converted->gobj1->GetName()
			+ " and " + converted->gobj2->GetName();
		TraceMessage(str.c_str());
	}

}

void SceneChangeCallback(void* eventData)
{
	SceneChangeEvent* converted = static_cast<SceneChangeEvent*>(eventData);
	if (converted)
	{
		TraceMessage(("SceneChangeEvent: "+ converted->SceneName).c_str());
		GameEngine::GetInstance()->AddSceneToChange(converted->SceneName);
	}
}