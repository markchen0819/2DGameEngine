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

	// Create Shader
	Shader sampleShader("src/SampleShader.vert", "src/SampleShader.frag");

	// Create Texture
	Texture sampleTexture("src/Assets/SampleTexture.jpg", "texture_diffuse");

	// Create Material
	Material sampleMaterial;
	sampleMaterial.AttachShader(&sampleShader);
	sampleMaterial.AttachTexture(&sampleTexture);
	Material sampleMaterial2;
	sampleMaterial2.SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	sampleMaterial2.AttachShader(&sampleShader);
	sampleMaterial2.AttachTexture(&sampleTexture);

	//Create Node
	//Node sampleNode(sampleTransform, sampleMesh, &sampleMaterial);

	//Create Triangles
	TriangleObject mytriangle;
	mytriangle.AttachMaterial(&sampleMaterial);
	TriangleObject mytriangle2;
	mytriangle2.AttachMaterial(&sampleMaterial2);
	mytriangle.AddChildNode(&mytriangle2); // Scene graph
	mytriangle2.transform->SetScale(0.5f, 0.5f, 0.5f);
	mytriangle2.transform->SetTranslation(0.0f, -50.0f, 0.0f);
	mytriangle2.transform->SetRotation(0, 0, 180.0f);

	// Use this shader
	sampleShader.useProgram();
	// Create camera
	Camera camera(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), mainWindow->Props.Heigth, mainWindow->Props.Width);
	camera.SetupVP(sampleShader);

	// Test vars to Scale, Rotate, Translate
	float val = 0;
	float timeToChangeDir = 1.0f;
	int dir = 1;

	while (!mainWindow->ShouldClose())// && !secondWindow->ShouldClose()
	{
		deltaTime = glfwGetTime() - lastFrameTime;
		if (deltaTime > expectedTimePerFrame)
		{
			lastFrameTime = glfwGetTime();
			mainWindow->Update();
			renderer.ClearScreen();

			// Test math to rotate, translate, scale
			timeToChangeDir = timeToChangeDir - deltaTime;
			if (timeToChangeDir < 0)
			{
				dir *= -1;
				timeToChangeDir = 1.0f;
			}
			val = val + dir * deltaTime * 5;


			//sampleNode.material->shader->useProgram();
			//sampleNode.transform->SetRotation(0, 0, val);
			//sampleNode.transform->SetTranslation(-100 + val * 40, -100 + val * 40, 0.0f);
			//sampleNode.transform->SetScale(1 + val / 10, 1 + val / 10, 1 + val / 10);
			//sampleNode.Draw();
			mytriangle.material->shader->useProgram();
			mytriangle.transform->SetRotation(0, 0, val*50);
			mytriangle.transform->SetTranslation(-100 + val * 40, -100 + val * 40, 0.0f);
			mytriangle.transform->SetScale(1 + val / 10, 1 + val / 10, 1 + val / 10);
			mytriangle.Draw();


			// swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			mainWindow->SwapBuffers();
			mainWindow->PollEvents();

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




