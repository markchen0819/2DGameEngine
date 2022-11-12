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
			//converted->gobj1->SetToBeDeleted();
		}
		if (converted->gobj2->GetName() != "Player")
		{
			converted->gobj2->SetAlive(false);
			//converted->gobj2->SetToBeDeleted();
		}
	}
}

void execute();
int main(int argc, char* argv[]) // Entry Point
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	execute();
	_CrtDumpMemoryLeaks();
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

	/////////////// User logic ///////////////////
	
	// Input
	InputManager* inputmanager = InputManager::GetInstance();
	inputmanager->Init(mainWindow);

	// ResourceManager
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	resourceManager->LoadAllShaders("src/Assets/Jsons/AllShaders.json");
	resourceManager->LoadAllTextures("src/Assets/Jsons/AllTextures.json");
	resourceManager->LoadAllMaterials("src/Assets/Jsons/AllMaterials.json");

	// ObjectFactory
	ObjectFactory* objectFactory = ObjectFactory::GetInstance();
	objectFactory->CreateAllGameObjects("src/Assets/Jsons/AllGameObjects.json");
	objectFactory->InitializeGameObjects();
	objectFactory->CreateAllDebugCollisionAreas();

	// Assign GameObjects from factory
	GameObject* player = objectFactory->GetGameObjectByName("Player");
	TransformComponent* playerTC = (*player).GetComponent<TransformComponent>();
	PhysicComponent* playerPC = (*player).GetComponent<PhysicComponent>();
	GameObject* playerChild = objectFactory->GetGameObjectByName("PlayerChild");
	(*player).AddChild(playerChild);
	GameObject* targetObj1 = objectFactory->GetGameObjectByName("Target1");
	GameObject* targetObj2 = objectFactory->GetGameObjectByName("Target2");
	TransformComponent* targetObj1TC = (*targetObj1).GetComponent<TransformComponent>();
	TransformComponent* targetObj2TC = (*targetObj2).GetComponent<TransformComponent>();


	// Create camera and Set Shader's View Projection uniform
	Shader* cameraShader = resourceManager->GetShaderByName("CameraShader");
	Shader* sampleShader = resourceManager->GetShaderByName("SampleShader");
	(*cameraShader).useProgram();
	Camera camera(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), mainWindow->Props.Heigth, mainWindow->Props.Width);
	camera.SetShaderVP(*cameraShader);
	(*renderer).UnuseShaderProgram();
	(*sampleShader).useProgram();
	camera.SetShaderVP(*sampleShader);
	(*renderer).UnuseShaderProgram();

	// Handle collisions
	PhysicsManager* physicsManager = PhysicsManager::GetInstance();
	(*physicsManager).collisionManager.AddGameObjectForCollisionChecking(player);
	(*physicsManager).collisionManager.AddGameObjectForCollisionChecking(targetObj1);
	(*physicsManager).collisionManager.AddGameObjectForCollisionChecking(targetObj2);

	//Eventsystem
	EventSystem* eventSystem = EventSystem::GetInstance();
	EventListener c(collisionCallback, EventType::Collision);
	eventSystem->AddListener(EventType::Collision, &c);


	while (!mainWindow->ShouldClose())// && !secondWindow->ShouldClose()
	{
		fpsController->FrameStart();
		////////////////////////////////

		mainWindow->Update();
		(*renderer).ClearScreen();

		// Input
		if (inputmanager->IsKeyDown(RIGHT))
		{
			playerPC->SetAngularVelocity(glm::vec3(0.0f, 0.0f, -5.0f));
		}
		if (inputmanager->IsKeyDown(LEFT))
		{
			playerPC->SetAngularVelocity(glm::vec3(0.0f, 0.0f, 5.0f));
		}
		if (inputmanager->IsKeyDown(UP))
		{
			playerPC->SetVelocity(glm::vec3(playerTC->GetRotationMatrix() * glm::vec4(0.0f, 5.0f, 0.0f, 1.0f)));
		}
		if (inputmanager->IsKeyDown(DOWN))
		{
			playerPC->SetVelocity(glm::vec3(playerTC->GetRotationMatrix() * glm::vec4(0.0f, -5.0f, 0.0f, 1.0f)));
		}


		targetObj1TC->SetRotation(0, 0, targetObj1TC->GetRotation().z + 100 * fpsController->DeltaTime());
		targetObj2TC->SetRotation(0, 0, targetObj1TC->GetRotation().z - 100 * fpsController->DeltaTime());

		//// Render ////

		(*player).Update();
		(*targetObj1).Update();
		(*targetObj2).Update();

		(*player).Draw();
		(*targetObj1).Draw();
		(*targetObj2).Draw();

		//// Physics ////
		(*physicsManager).collisionManager.CheckAllCollisions();
		(*physicsManager).Integrate();

		// Swap buffers and poll IO events
		mainWindow->SwapBuffers();
		mainWindow->PollEvents();  // Window events
		inputmanager->PollEvents();// Input events

		//ExecuteScreenSaverMovement(mainWindow, deltaTime);
		// Experimenting 2nd window
		//secondWindow->Update();
		objectFactory->DeferredDeleteGameObjects();
		////////////////////////////////
		fpsController->FrameEnd();
	}
	//objectFactory->DestroyAllGameObjects();
	(*player).Destroy();
	(*targetObj1).Destroy();
	(*targetObj2).Destroy();

	/////////////// User logic ///////////////////

	//secondWindow->ShutDown();
    //delete secondWindow;
	mainWindow->ShutDown();
	delete mainWindow;

	(*renderer).TerminateGLFW();
	TraceShutdown();

}



