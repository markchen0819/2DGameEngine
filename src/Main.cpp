#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "pch.h"

void collisionCallback(void* eventData)
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

void execute();
int main(int argc, char* argv[]) // Entry Point
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	execute();
}
void execute() // All code to excute (for CRT detect memory leak and VS heap snapshot)
{
	TraceInit();

	Renderer* renderer = Renderer::GetInstance();
	(*renderer).InitGLFW();

	GameWindow* mainWindow = new GameWindow();
	mainWindow->Props.Title = "1stWindow";
	mainWindow->Init();
	mainWindow->SetWindowPosition(0, 50);
	// Experimenting 2nd window
	//GameWindow* secondWindow = new GameWindow();
	//secondWindow->Props.Title = "2ndWindow";
	//secondWindow->Init();

	FrameRateController* fpsController = FrameRateController::GetInstance();
	fpsController->SetTargetFrameRate(60.0);

	InputManager* inputmanager = InputManager::GetInstance();
	inputmanager->Init(mainWindow);

	EventSystem* eventSystem = EventSystem::GetInstance();
	EventListener c(collisionCallback, EventType::Collision);
	eventSystem->AddListener(EventType::Collision, &c);

	Scene scene;
	scene.LoadResources("src/Assets/Jsons/AllResources.json");
	scene.LoadGameObjects("src/Assets/Jsons/AllGameObjects.json");
	scene.BuildHiearchy("src/Assets/Jsons/Hierachy.json");
	scene.SetupCamara(mainWindow);

	while (!mainWindow->ShouldClose())// && !secondWindow->ShouldClose()
	{
		fpsController->FrameStart();
		mainWindow->Update();
		(*renderer).ClearScreen();

		scene.Update();
		scene.Draw();
		scene.LateUpdate();

		mainWindow->SwapBuffers();
		mainWindow->PollEvents(); 
		inputmanager->PollEvents();

		//ExecuteScreenSaverMovement(mainWindow, deltaTime);
		// Experimenting 2nd window
		//secondWindow->Update();

		fpsController->FrameEnd();
	}
	scene.Destroy();

	//secondWindow->ShutDown();
    //delete secondWindow;
	mainWindow->ShutDown();
	delete mainWindow;

	(*renderer).TerminateGLFW();
	TraceShutdown();
}



