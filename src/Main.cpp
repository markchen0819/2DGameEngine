#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include "GameWindow.h"
#include "Experiment/ScreenSaverMovement.h"
#include "Logging.h"
#include "Graphics/Renderer.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "Graphics/Material.h"
#include "Graphics/Mesh.h";
#include "Graphics/Node.h"
#include "Camera.h"

#include "UserDefined/TriangleObject.h"
#include "InputManager.h"
#include "Physics/CollisionManager.h"
#include "GameObject.h"
#include "Physics/CollisionCircle.h"
#include "Physics/CollisionAABB.h"
#include "EventSystem.h"

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
	mainWindow->SetWindowPosition(50, 50);
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
	InputManager inputmanager = InputManager::GetInstance();
	inputmanager.Init(mainWindow);

	// Create Shader
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

	////// Create Graphic Nodes ( UserDefined Triangle class ) //////
	// Player Nodes
	TriangleObject mytriangle;
	mytriangle.AttachMaterial(&sampleMaterial);
	TriangleObject mytriangle2;
	mytriangle2.AttachMaterial(&sampleMaterial2);
	mytriangle.AddChildNode(&mytriangle2); // Scene graph
	mytriangle2.transform->SetScale(0.3f, 0.3f, 0.3f);
	mytriangle2.transform->SetTranslation(50.0f, -70.0f, 0.0f);
	mytriangle2.transform->SetRotation(0, 0, 180.0f);
	TriangleObject mytriangle3;
	mytriangle3.AttachMaterial(&sampleMaterial2);
	mytriangle.AddChildNode(&mytriangle3); // Scene graph
	mytriangle3.transform->SetScale(0.3f, 0.3f, 0.3f);
	mytriangle3.transform->SetTranslation(-50.0f, -70.0f, 0.0f);
	mytriangle3.transform->SetRotation(0, 0, 180.0f);
	// TargetObject Node
	TriangleObject targetT;
	targetT.AttachMaterial(&sampleMaterial);
	targetT.transform->SetTranslation(200.0f, 0.0f, 0.0f);

	////// Create bodies and collision shapes //////

	CollisionManager collisionManager;

	Body playerBody;
	playerBody.AttachTransform(mytriangle.transform);
	Body targetBody;
	targetBody.AttachTransform(targetT.transform);

	CollisionAABB ab1(100, -100, 100, -100);
	//CollisionCircle ab1(100);
	ab1.collisionAreaObject->AttachMaterial(&collisionMaterial);
	playerBody.collisionShape = &ab1;


	CollisionAABB ab2(100, -100, 100, -100);
	//CollisionCircle ab2(100);
	ab2.collisionAreaObject->AttachMaterial(&collisionMaterial);
	targetBody.collisionShape = &ab2;

	//// Attach graphic and physic body to gameobj

	GameObject player;
	player.Name = "Player";
	player.AttachNode(&mytriangle);
	player.AttachBody(&playerBody);

	GameObject targetObj;
	targetObj.Name = "Target";
	targetObj.AttachNode(&targetT);
	targetObj.AttachBody(&targetBody);


	//test eventsystem
//EventSystem eventSystem = EventSystem::GetInstance();
	using namespace std::placeholders;
	//CollisionEventListener c;
	//eventSystem.RegisterEvent(EventType::Collision, std::bind(&CollisionEventListener::HandleEvent, c, _1));




	// Create camera
	sampleShader.useProgram();
	Camera camera(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), mainWindow->Props.Heigth, mainWindow->Props.Width);
	camera.SetupVP(sampleShader);

	// Old test vars for Old direct input for transform
	/*
	// Test vars to Scale, Rotate, Translate
	float val = 0;
	int dir = 0;
	float x = 0.0f;
	float y = 0.0f;*/

	while (!mainWindow->ShouldClose())// && !secondWindow->ShouldClose()
	{
		deltaTime = glfwGetTime() - lastFrameTime;
		if (deltaTime > expectedTimePerFrame)
		{
			lastFrameTime = glfwGetTime();
			mainWindow->Update();
			renderer.ClearScreen();

			// Old direct input for transform
			/*if (inputmanager.IsKeyDown(RIGHT))
			{
				x += 5.0f;
				dir = 270;
			}
			if (inputmanager.IsKeyDown(LEFT))
			{
				x -= 5.0f;
				dir = 90;
			}
			if (inputmanager.IsKeyDown(UP))
			{
				y += 5.0f;
				dir = 0;
			}
			if (inputmanager.IsKeyDown(DOWN))
			{
				y -= 5.0f;
				dir = 180;
			}
			if (inputmanager.IsKeyDown(RIGHT) && inputmanager.IsKeyDown(UP))
			{
				dir = 315;
			}
			else if (inputmanager.IsKeyDown(RIGHT) && inputmanager.IsKeyDown(DOWN))
			{
				dir = 225;
			}
			else if (inputmanager.IsKeyDown(LEFT) && inputmanager.IsKeyDown(UP))
			{
				dir = 45;
			}
			else if (inputmanager.IsKeyDown(LEFT) && inputmanager.IsKeyDown(DOWN))
			{
				dir = 135;
			}
			player.node->transform->SetRotation(0, 0, dir);
			player.node->transform->SetTranslation(x, y, 0.0f);
			player.node->transform->SetScale(0.5+y/500, 0.5 + y / 500, 0.5 + y / 500);*/

			// New input to Physics body then feed to transform
			if (inputmanager.IsKeyDown(RIGHT))
			{
				player.body->AngularVelocity = glm::vec3(0.0f, 0.0f, -5.0f);
			}
			if (inputmanager.IsKeyDown(LEFT))
			{
				player.body->AngularVelocity = glm::vec3(0.0f, 0.0f, 5.0f);
			}
			if (inputmanager.IsKeyDown(UP))
			{
				glm::mat4 playerRotationMatrix = player.node->transform->GetRotationMatrix();
				player.body->Velocity =
					glm::vec3(playerRotationMatrix * glm::vec4(0.0f, 5.0f, 0.0f, 1.0f));
			}
			if (inputmanager.IsKeyDown(DOWN))
			{
				glm::mat4 playerRotationMatrix = player.node->transform->GetRotationMatrix();
				player.body->Velocity =
					glm::vec3(playerRotationMatrix * glm::vec4(0.0f, -5.0f, 0.0f, 1.0f));
			}

			player.node->transform->SetRotation(0, 0, player.body->Rotation.z);
			player.node->transform->SetTranslation(player.body->Position.x, player.body->Position.y, 0.0f);
			player.body->UpdateTransform();
			targetObj.body->UpdateTransform();


			player.Draw();
			targetObj.Draw();
			// Debug, draw collision area
			player.body->collisionShape->collisionAreaObject->Draw();
			targetObj.body->collisionShape->collisionAreaObject->Draw();

			//if (collisionManager.CheckCollision(player.body->collisionShape, x, y, targetObj.body->collisionShape, targetObj.body->transform->GetPosition().x, targetObj.body->transform->GetPosition().y))
			//{
			//	std::cout << glfwGetTime() << "_Collide!" << std::endl;
			//	CollisionEvent c = CollisionEvent();
			//	c.gobj1 = &player;
			//	c.gobj2 = &targetObj;
			//	//eventSystem.BroadcastEvent(&c);
			//}
			

			player.body->Integrate();
			targetObj.body->Integrate();

			// swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			mainWindow->SwapBuffers();
			mainWindow->PollEvents(); // Window events
			inputmanager.PollEvents();// Input events

			//ExecuteScreenSaverMovement(mainWindow, deltaTime);
			// Experimenting 2nd window
			//secondWindow->Update();
		}
	}

	/////////////// User logic ///////////////////

	//secondWindow->ShutDown();
    //delete secondWindow;
	mainWindow->ShutDown();
	delete mainWindow;

	renderer.TerminateGLFW();
	TraceShutdown();
}



