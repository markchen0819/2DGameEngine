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
#include "Physics/CollisionOBB.h"
#include "EventSystem/EventSystem.h"

void callbackForCollision(void *eventData)
{
	std::cout << "callbackForCollision" << std::endl;
	//std::cout << "eventData raw argument was : '" << eventData << "'" << std::endl;

	CollisionEvent* converted = static_cast<CollisionEvent*>(eventData);
	if (converted)
	{
		std::cout <<"TimeStamp: "<<glfwGetTime() << std::endl;
		std::cout << "Collision between " << converted->gobj1.Name 
			<<" and "<< converted->gobj2.Name << std::endl;
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
	TriangleObject targetT2;
	targetT2.AttachMaterial(&sampleMaterial2);
	targetT2.transform->SetTranslation(0.0f, 300.0f, 0.0f);
	targetT2.transform->SetRotation(0.0f, 0.0f, 45.0f);
	targetT2.transform->SetScale(0.5f, 0.5f, 0.0f);
	////// Create bodies and collision shapes //////

	CollisionManager collisionManager;

	Body playerBody;
	playerBody.AttachTransform(mytriangle.transform);
	playerBody.GetCollisionAreaObject().AttachMaterial(&collisionMaterial);
	Body targetBody;
	targetBody.AttachTransform(targetT.transform);
	targetBody.GetCollisionAreaObject().AttachMaterial(&collisionMaterial);
	Body targetBody2;
	targetBody2.AttachTransform(targetT2.transform);
	targetBody2.GetCollisionAreaObject().AttachMaterial(&collisionMaterial);

	// AABB
	//CollisionAABB c1(100, -100, 100, -100);
	//CollisionAABB c2(100, -100, 100, -100);
	//playerBody.GetCollisionAreaObject().SetMesh(100, -100, 100, -100);
	//targetBody.GetCollisionAreaObject().SetMesh(100, -100, 100, -100);

	// Circle
	//CollisionCircle c1(100);
	//CollisionCircle c2(100);
	//playerBody.GetCollisionAreaObject().SetMesh(100);
	//targetBody.GetCollisionAreaObject().SetMesh(100);

	// OBB
	std::vector<glm::vec4> obbVerticies;
	// Box vertices
	obbVerticies.push_back(glm::vec4(100.0f, 100.0f, 0.0f, 1.0f));
	obbVerticies.push_back(glm::vec4(100.0f, -100.0f, 0.0f, 1.0f));
	obbVerticies.push_back(glm::vec4(-100.0f, -100.0f, 0.0f, 1.0f));
	obbVerticies.push_back(glm::vec4(-100.0f, 100.0f, 0.0f, 1.0f));
	// Polygon vertices (SAT supports polygons)
	//obbVerticies.push_back(glm::vec4(120.0f, 100.0f, 0.0f, 1.0f));
	//obbVerticies.push_back(glm::vec4(80.0f, -100.0f, 0.0f, 1.0f));
	//obbVerticies.push_back(glm::vec4(-120.0f, -100.0f, 0.0f, 1.0f));
	//obbVerticies.push_back(glm::vec4(-80.0f, 100.0f, 0.0f, 1.0f));
	CollisionOBB c1(obbVerticies);
	CollisionOBB c2(obbVerticies);
	CollisionOBB c3(obbVerticies);
	playerBody.GetCollisionAreaObject().SetMesh(obbVerticies);
	targetBody.GetCollisionAreaObject().SetMesh(obbVerticies);
	targetBody2.GetCollisionAreaObject().SetMesh(obbVerticies);

	playerBody.collisionShape = &c1;
	targetBody.collisionShape = &c2;
	targetBody2.collisionShape = &c3;

	////// Attach graphic and physic body to gameobj //////
	GameObject player;
	player.Name = "Player";
	player.AttachNode(&mytriangle);
	player.AttachBody(&playerBody);

	GameObject targetObj;
	targetObj.Name = "Target";
	targetObj.AttachNode(&targetT);
	targetObj.AttachBody(&targetBody);

	GameObject targetObj2;
	targetObj2.Name = "Target2";
	targetObj2.AttachNode(&targetT2);
	targetObj2.AttachBody(&targetBody2);
	// Add gameObjects for broad phase collision checking
	collisionManager.AddGameObjectForCollisionChecking(&player);
	collisionManager.AddGameObjectForCollisionChecking(&targetObj);
	collisionManager.AddGameObjectForCollisionChecking(&targetObj2);

	//Test eventsystem
	EventSystem& eventSystem = EventSystem::GetInstance();
	EventListener c(callbackForCollision, EventType::Collision);
	eventSystem.AddListener(EventType::Collision, &c);

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
			
			// Check if collision scale working properly
			player.body->Scale = glm::vec3(0.5 + player.body->Position.y/500, 0.5 + player.body->Position.y / 500, 0.5 + player.body->Position.y / 500);

			player.node->transform->SetRotation(0, 0, player.body->Rotation.z);
			player.node->transform->SetTranslation(player.body->Position.x, player.body->Position.y, 0.0f);
			player.node->transform->SetScale(player.body->Scale.x, player.body->Scale.y, player.body->Scale.z);

			//player.node->transform->PrintTransform();

			player.Draw();
			targetObj.Draw();
			targetObj2.Draw();

			// Debug, draw collision area
			player.body->GetCollisionAreaObject().Draw(); 
			targetObj.body->GetCollisionAreaObject().Draw();
			targetObj2.body->GetCollisionAreaObject().Draw();
			player.body->Integrate();
			targetObj.body->Integrate();
			targetObj2.body->Integrate();

			collisionManager.CheckAllCollisions();

			//CollisionEvent c = CollisionEvent();
			//c.gobj1 = &player;
			//c.gobj2 = &targetObj;
			//eventSystem.BroadcastEvent(&c);

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



