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
		std::cout << "Collision between " << converted->gobj1->Name
			<< " and " << converted->gobj2->Name << std::endl;
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

	// Create GameObjects
	GameObject player;
	player.Name = "Player";
	player.SetMaterial(&sampleMaterial);
	player.AddComponent<TransformComponent>();
	player.AddComponent<RenderComponent>();
	player.AddComponent<PhysicComponent>();

	GameObject targetObj;
	targetObj.Name = "Target";
	targetObj.SetMaterial(&sampleMaterial2);
	targetObj.AddComponent<TransformComponent>();
	targetObj.AddComponent<RenderComponent>();
	targetObj.AddComponent<PhysicComponent>();

	GameObject targetObj2;
	targetObj2.Name = "Target2";
	targetObj2.SetMaterial(&sampleMaterial2);
	targetObj2.AddComponent<TransformComponent>();
	targetObj2.AddComponent<RenderComponent>();
	targetObj2.AddComponent<PhysicComponent>();

	GameObject child;
	child.Name = "child";
	child.SetMaterial(&sampleMaterial2);
	child.AddComponent<TransformComponent>();
	child.AddComponent<RenderComponent>();

	// Create Debug Nodes (For viewing collision area)
	CollisionAreaObject playerCAO;
	//playerCAO.SetMesh(obbVerticies); // Use default shape for now
	playerCAO.Name = "Player Collision Area";
	playerCAO.SetMaterial(&collisionMaterial);
	CollisionAreaObject targetObjCAO;
	targetObjCAO.Name = "targetObj Collision Area";
	targetObjCAO.SetMaterial(&collisionMaterial);
	CollisionAreaObject targetObj2CAO;
	targetObj2CAO.Name = "targetObj2 Collision Area";
	targetObj2CAO.SetMaterial(&collisionMaterial);


	player.AddChild(&child);
	player.AddChild(&playerCAO);
	targetObj.AddChild(&targetObjCAO);
	targetObj2.AddChild(&targetObj2CAO);

	player.Init();
	targetObj.Init();
	targetObj2.Init();
	//child.Init();
	
	//GetComponent after Init
	child.GetComponent<TransformComponent>()->SetTranslation(0, -200, 0);
	child.GetComponent<TransformComponent>()->SetScale(0.5, 0.5, 0.5);
	TransformComponent* playerTC = player.GetComponent<TransformComponent>();
	PhysicComponent* playerPC = player.GetComponent<PhysicComponent>();

	// Handle collisions
	PhysicsManager* physicsManager = PhysicsManager::GetInstance();
	(*physicsManager).collisionManager.AddGameObjectForCollisionChecking(&player);
	(*physicsManager).collisionManager.AddGameObjectForCollisionChecking(&targetObj);
	(*physicsManager).collisionManager.AddGameObjectForCollisionChecking(&targetObj2);

	//Eventsystem
	EventSystem* eventSystem = EventSystem::GetInstance();
	EventListener c(collisionCallback, EventType::Collision);
	eventSystem->AddListener(EventType::Collision, &c);

	// Create camera and Set Shader's View Projection uniform
	cameraShader.useProgram();
	Camera camera(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), mainWindow->Props.Heigth, mainWindow->Props.Width);
	camera.SetShaderVP(cameraShader);
	(*renderer).UnuseShaderProgram();
	sampleShader.useProgram();
	camera.SetShaderVP(sampleShader);
	(*renderer).UnuseShaderProgram();

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
			glm::vec3 newScale = glm::vec3(0.5 + playerPC->GetPosition().y / 500, 0.5 + playerPC->GetPosition().y / 500, 0.5 + playerPC->GetPosition().y / 500);
			playerTC->SetScale(newScale.x, newScale.y, newScale.z);
			targetObj.GetComponent<TransformComponent>()->SetTranslation(200, 0, 0);
			targetObj2.GetComponent<TransformComponent>()->SetTranslation(0, -200, 0);

			//// Render ////
			player.Update();
			targetObj.Update();
			targetObj2.Update();
			player.Draw();
			targetObj.Draw();
			targetObj2.Draw();

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
	player.Destroy();
	targetObj.Destroy();
	targetObj2.Destroy();

	/////////////// User logic ///////////////////

	//secondWindow->ShutDown();
    //delete secondWindow;
	mainWindow->ShutDown();
	delete mainWindow;

	(*renderer).TerminateGLFW();
	TraceShutdown();

}



