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

	// Lock FPS
	float FPS = 60;
	float expectedTimePerFrame = 1.0 / FPS;
	float lastFrameTime = glfwGetTime();
	float deltaTime = 0;

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
	//// User defined Object Creation
	/*

	// Create Debug Nodes (For viewing collision area)
	CollisionAreaObject playerCAO;
	//playerCAO.SetMesh(obbVerticies); // Use default shape for now
	playerCAO.SetName("Player Collision Area");
	playerCAO.SetMaterial(&collisionMaterial);
	CollisionAreaObject targetObjCAO;
	targetObjCAO.SetName("targetObj Collision Area");
	targetObjCAO.SetMaterial(&collisionMaterial);
	CollisionAreaObject targetObj2CAO;
	targetObj2CAO.SetName( "targetObj2 Collision Area");
	targetObj2CAO.SetMaterial(&collisionMaterial);
	

	player.AddChild(&child);
	player.AddChild(&playerCAO);
	targetObj.AddChild(&targetObjCAO);
	targetObj2.AddChild(&targetObj2CAO);


	*/


	// Assign GameObjects from factory
	GameObject* player = objectFactory->GetGameObjectByName("Player");
	TransformComponent* playerTC = (*player).GetComponent<TransformComponent>();
	PhysicComponent* playerPC = (*player).GetComponent<PhysicComponent>();
	GameObject* playerChild = objectFactory->GetGameObjectByName("PlayerChild");
	(*player).AddChild(playerChild);
	GameObject* targetObj1 = objectFactory->GetGameObjectByName("Target1");
	TransformComponent* targetObj1TC = (*targetObj1).GetComponent<TransformComponent>();
	GameObject* targetObj2 = objectFactory->GetGameObjectByName("Target2");
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

	// Create Debug Nodes (For viewing collision area)
	CollisionAreaObject playerCAO;
	//playerCAO.SetMesh(obbVerticies); // Use default shape for now
	playerCAO.SetName("Player Collision Area");
	playerCAO.SetMaterial(resourceManager->GetMaterialByName("CollisionMaterial"));
	CollisionAreaObject targetObjCAO;
	targetObjCAO.SetName("targetObj Collision Area");
	targetObjCAO.SetMaterial(resourceManager->GetMaterialByName("CollisionMaterial"));
	CollisionAreaObject targetObj2CAO;
	targetObj2CAO.SetName("targetObj2 Collision Area");
	targetObj2CAO.SetMaterial(resourceManager->GetMaterialByName("CollisionMaterial"));


	(*player).AddChild(&playerCAO);
	(*targetObj1).AddChild(&targetObjCAO);
	(*targetObj2).AddChild(&targetObj2CAO);


	while (!mainWindow->ShouldClose())// && !secondWindow->ShouldClose()
	{
		deltaTime = glfwGetTime() - lastFrameTime;
		if (deltaTime > expectedTimePerFrame)
		{
			lastFrameTime = glfwGetTime();
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

			targetObj1TC->SetRotation(0, 0, targetObj1TC->GetRotation().z + 1);
			targetObj2TC->SetRotation(0, 0, targetObj2TC->GetRotation().z + 1);
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
		}
	}
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



