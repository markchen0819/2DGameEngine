#include <iostream>
#include "GameWindow.h"
#include "ScreenSaverMovement.h"
#include "Logging.h"
#include "Renderer.h"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h";
#include "Node.h"

#include "UserDefined/TriangleObject.h"
#include "InputManager.h"

int main(int argc, char* argv[])
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
	Shader sampleShader("src/SampleShader.vert", "src/SampleShader.frag");

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

	//Create Node
	//Node sampleNode(sampleTransform, sampleMesh, &sampleMaterial);

	//Create Triangles
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

	// Use this shader
	sampleShader.useProgram();
	// Create camera
	Camera camera(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), mainWindow->Props.Heigth, mainWindow->Props.Width);
	camera.SetupVP(sampleShader);

	// Test vars to Scale, Rotate, Translate
	float val = 0;
	int dir = 0;
	float x = 0.0f;
	float y = 0.0f;

	while (!mainWindow->ShouldClose())// && !secondWindow->ShouldClose()
	{
		deltaTime = glfwGetTime() - lastFrameTime;
		if (deltaTime > expectedTimePerFrame)
		{
			lastFrameTime = glfwGetTime();
			mainWindow->Update();
			renderer.ClearScreen();

			//sampleNode.material->shader->useProgram();
			//sampleNode.transform->SetRotation(0, 0, val);
			//sampleNode.transform->SetTranslation(-100 + val * 40, -100 + val * 40, 0.0f);
			//sampleNode.transform->SetScale(1 + val / 10, 1 + val / 10, 1 + val / 10);
			//sampleNode.Draw();

			if (inputmanager.IsKeyDown(RIGHT))
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


			//mytriangle.material->shader->useProgram();
			mytriangle.transform->SetRotation(0, 0, dir);
			mytriangle.transform->SetTranslation(x, y, 0.0f);
			mytriangle.transform->SetScale(0.5+y/500, 0.5 + y / 500, 0.5 + y / 500);
			mytriangle.Draw();


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
	mainWindow->ShutDown();
	renderer.TerminateGLFW();
	TraceShutdown();

	return 0;
}




