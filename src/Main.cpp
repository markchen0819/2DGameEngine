#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include "Allheaders.h"


void callbackForCollision(void *eventData)
{
	std::cout << "callbackForCollision" << std::endl;
	//std::cout << "eventData raw argument was : '" << eventData << "'" << std::endl;

	CollisionEvent* converted = static_cast<CollisionEvent*>(eventData);
	if (converted)
	{
		std::cout <<"TimeStamp: "<<glfwGetTime() << std::endl;
		std::cout << "Collision between "
			<< converted->gobj1->Name 
			<<" and "<< converted->gobj2->Name << std::endl;
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

	Renderer renderer;
	renderer.InitGLFW();

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

	// Create Shader
	Shader cameraShader("src/Graphics/SampleShader.vert", "src/Graphics/SampleShader.frag");
	Shader sampleShader("src/Graphics/SampleShader.vert", "src/Graphics/SampleShader.frag");

	// Create Texture
	Texture sampleTexture("src/Assets/SampleTexture.jpg", "texture_diffuse");
	Texture sampleTexture2("src/Assets/DefaultTexture.jpg", "texture_diffuse");

	// Create Material
	Material sampleMaterial;
	sampleMaterial.AttachShader(&sampleShader);
	sampleMaterial.AttachTexture(&sampleTexture);
    Material sampleMaterial2;
	sampleMaterial2.SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	sampleMaterial2.AttachShader(&sampleShader);
	sampleMaterial2.AttachTexture(&sampleTexture2);
	Material collisionMaterial;
	collisionMaterial.SetColor(0.0f, 1.0f, 0.0f, 1.0f);
	collisionMaterial.AttachShader(&sampleShader);
	collisionMaterial.AttachTexture(&sampleTexture);


	GameObject scene;
	scene.Init();
	// Create GameObjects
	GameObject player;
	player.Name = "Player";
	player.SetMaterial(&sampleMaterial);
	player.AddComponent<TransformComponent>();
	player.AddComponent<RenderComponent>();
	player.AddComponent<PhysicComponent>();
	player.Init();
	TransformComponent* playerTC = player.GetComponent<TransformComponent>();
	PhysicComponent* playerPC = player.GetComponent<PhysicComponent>();
	playerPC->GetCollisionAreaObject().SetName("Player Collision Area");
	playerPC->GetCollisionAreaObject().AttachMaterial(&collisionMaterial);
	scene.AddChild(&player);

	GameObject targetObj;
	targetObj.Name = "Target";
	targetObj.SetMaterial(&sampleMaterial2);
	targetObj.AddComponent<TransformComponent>();
	targetObj.AddComponent<RenderComponent>();
	targetObj.AddComponent<PhysicComponent>();
	targetObj.Init();
	PhysicComponent* targetObjPC = targetObj.GetComponent<PhysicComponent>();
	targetObjPC->GetCollisionAreaObject().SetName("targetObj Collision Area");
	targetObjPC->GetCollisionAreaObject().AttachMaterial(&collisionMaterial);
	scene.AddChild(&targetObj);

	GameObject child;
	child.Name = "child";
	child.SetMaterial(&sampleMaterial2);
	child.AddComponent<TransformComponent>();
	child.AddComponent<RenderComponent>();
	child.Init();

	child.GetTransform()->SetTranslation(0, -200, 0);
	child.GetTransform()->SetScale (0.5, 0.5, 0.5);
	player.AddChild(&child);

	// Handle collision and events
	CollisionManager collisionManager;
	collisionManager.AddGameObjectForCollisionChecking(&player);
	collisionManager.AddGameObjectForCollisionChecking(&targetObj);

	//Eventsystem
	EventSystem* eventSystem = EventSystem::GetInstance();
	EventListener c(callbackForCollision, EventType::Collision);
	eventSystem->AddListener(EventType::Collision, &c);

	// Create camera
	cameraShader.useProgram();
	Camera camera(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), mainWindow->Props.Heigth, mainWindow->Props.Width);
	camera.SetupVP(cameraShader);
	renderer.UnuseShaderProgram();
	// Set projection and view uniform for sampleShader 
	sampleShader.useProgram();
	camera.SetupVP(sampleShader);
	renderer.UnuseShaderProgram();

	while (!mainWindow->ShouldClose())// && !secondWindow->ShouldClose()
	{
		deltaTime = glfwGetTime() - lastFrameTime;
		if (deltaTime > expectedTimePerFrame)
		{
			lastFrameTime = glfwGetTime();
			mainWindow->Update();
			renderer.ClearScreen();


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
			glm::vec3 newScale = glm::vec3(0.5 + playerPC->GetPosition().y / 500, 0.5 + playerPC->GetPosition().y / 500, 0.5 + playerPC->GetPosition().y / 500);
			playerTC->SetScale(newScale.x, newScale.y, newScale.z);
			targetObj.GetTransform()->SetTranslation(200, 0, 0);


			//// Check collision ////
			collisionManager.CheckAllCollisions();

			//// Apply physics ////
			scene.Update();
			//player.Update();
			//targetObj.Update();
			// PC intergrates, TC was fed new values, RC Draws

			// swap buffers and poll IO events
			mainWindow->SwapBuffers();
			mainWindow->PollEvents(); // Window events
			inputmanager->PollEvents();// Input events

			//ExecuteScreenSaverMovement(mainWindow, deltaTime);
			// Experimenting 2nd window
			//secondWindow->Update();
		}
	}
	player.Destroy();
	targetObj.Destroy();
	/////////////// User logic ///////////////////

	//secondWindow->ShutDown();
    //delete secondWindow;
	mainWindow->ShutDown();
	delete mainWindow;

	renderer.TerminateGLFW();
	TraceShutdown();

}



