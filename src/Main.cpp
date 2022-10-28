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
		std::cout << "Collision between ";
			//<< converted->gobj1.Name 
			//<<" and "<< converted->gobj2.Name << std::endl;
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
	Shader sampleShader("src/Graphics/SampleShader.vert", "src/Graphics/SampleShader.frag");

	// Create Texture
	Texture sampleTexture("src/Assets/SampleTexture.jpg", "texture_diffuse");
	Texture sampleTexture2("src/Assets/DefaultTexture.jpg", "texture_diffuse");

	// Create Material
	Material sampleMaterial;
	sampleMaterial.AttachShader(&sampleShader);
	sampleMaterial.AttachTexture(&sampleTexture);
	//Material sampleMaterial2;
	//sampleMaterial2.SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	//sampleMaterial2.AttachShader(&sampleShader);
	//sampleMaterial2.AttachTexture(&sampleTexture2);
	//Material collisionMaterial;
	//collisionMaterial.SetColor(0.0f, 1.0f, 0.0f, 1.0f);
	//collisionMaterial.AttachShader(&sampleShader);
	//collisionMaterial.AttachTexture(&sampleTexture);

	////// Create Graphic Nodes ( UserDefined Triangle class ) //////
	


	////// Create bodies and collision shapes //////

	//CollisionManager collisionManager;

	//Body playerBody;
	//playerBody.AttachTransform(mytriangle.transform);
	//playerBody.GetCollisionAreaObject().AttachMaterial(&collisionMaterial);
	//Body targetBody;
	//targetBody.AttachTransform(targetT.transform);
	//targetBody.GetCollisionAreaObject().AttachMaterial(&collisionMaterial);
	//Body targetBody2;
	//targetBody2.AttachTransform(targetT2.transform);
	//targetBody2.GetCollisionAreaObject().AttachMaterial(&collisionMaterial);


	//// OBB
	//std::vector<glm::vec4> obbVerticies;
	//// Box vertices
	//obbVerticies.push_back(glm::vec4(100.0f, 100.0f, 0.0f, 1.0f));
	//obbVerticies.push_back(glm::vec4(100.0f, -100.0f, 0.0f, 1.0f));
	//obbVerticies.push_back(glm::vec4(-100.0f, -100.0f, 0.0f, 1.0f));
	//obbVerticies.push_back(glm::vec4(-100.0f, 100.0f, 0.0f, 1.0f));

	//CollisionOBB c1(obbVerticies);
	//CollisionOBB c2(obbVerticies);
	//CollisionOBB c3(obbVerticies);
	//playerBody.GetCollisionAreaObject().SetMesh(obbVerticies);
	//targetBody.GetCollisionAreaObject().SetMesh(obbVerticies);
	//targetBody2.GetCollisionAreaObject().SetMesh(obbVerticies);

	//playerBody.collisionShape = &c1;
	//targetBody.collisionShape = &c2;
	//targetBody2.collisionShape = &c3;

	////// Attach graphic and physic body to gameobj //////

	GameObject player;
	//player.Name = "Player";
	//player.AttachNode(&mytriangle);
	//player.AttachBody(&playerBody);

	//GameObject targetObj;
	//targetObj.Name = "Target";
	//targetObj.AttachNode(&targetT);
	//targetObj.AttachBody(&targetBody);

	//GameObject targetObj2;
	//targetObj2.Name = "Target2";
	//targetObj2.AttachNode(&targetT2);
	//targetObj2.AttachBody(&targetBody2);

	// Add gameObjects for broad phase collision checking
	/*collisionManager.AddGameObjectForCollisionChecking(&player);
	collisionManager.AddGameObjectForCollisionChecking(&targetObj);
	collisionManager.AddGameObjectForCollisionChecking(&targetObj2);*/

	//Eventsystem
	//EventSystem* eventSystem = EventSystem::GetInstance();
	//EventListener c(callbackForCollision, EventType::Collision);
	//eventSystem->AddListener(EventType::Collision, &c);

	// Create camera
	sampleShader.useProgram();
	Camera camera(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), mainWindow->Props.Heigth, mainWindow->Props.Width);
	camera.SetupVP(sampleShader);


	//
	player.SetMaterial(&sampleMaterial);
	TransformComponent tc;
	RenderComponent rc;
	PhysicComponent pc;

	player.AddComponent(&tc);
	player.AddComponent(&rc);
	player.AddComponent(&pc);
	tc.Init();
	rc.Init();
	pc.Init();
	PhysicComponent* playerPC = player.GetComponent<PhysicComponent>();
	TransformComponent* playerTC = player.GetComponent<TransformComponent>();

	while (!mainWindow->ShouldClose())// && !secondWindow->ShouldClose()
	{
		deltaTime = glfwGetTime() - lastFrameTime;
		if (deltaTime > expectedTimePerFrame)
		{
			lastFrameTime = glfwGetTime();
			mainWindow->Update();
			renderer.ClearScreen();



			//// New input to Physics body ////
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
			// Check if collision scale working properly
			
			glm::vec3 newScale = glm::vec3(0.5 + playerPC->GetPosition().y / 500, 0.5 + playerPC->GetPosition().y / 500, 0.5 + playerPC->GetPosition().y / 500);
			playerPC->SetScale(newScale);

			//// Feed to transform ////
			playerTC->SetRotation(0, 0, playerPC->GetRotation().z);
			playerTC->SetTranslation(playerPC->GetPosition().x, playerPC->GetPosition().y, playerPC->GetPosition().z);
			playerTC->SetScale(playerPC->GetScale().x, playerPC->GetScale().y, playerPC->GetScale().z);
			//player.node->transform->PrintTransform();

			// Draw Gobjs and collision area(Debug)
			player.Draw();
			//targetObj.Draw();
			//targetObj2.Draw();
			//player.body->GetCollisionAreaObject().Draw(); 
			//targetObj.body->GetCollisionAreaObject().Draw();
			//targetObj2.body->GetCollisionAreaObject().Draw();

			//// Check collision ////
			//collisionManager.CheckAllCollisions();

			//// Apply physics ////
			
			player.Update();
			//player.body->Integrate();
			//targetObj.body->Integrate();
			//targetObj2.body->Integrate();

			// swap buffers and poll IO events
			mainWindow->SwapBuffers();
			mainWindow->PollEvents(); // Window events
			inputmanager->PollEvents();// Input events

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



