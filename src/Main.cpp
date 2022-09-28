#include <iostream>
#include "GameWindow.h"
#include "Logging.h"
#include "ScreenSaverMovement.h"

int main(int argc, char* argv[])
{
	TraceInit();

	// Init GLFW here for multiple windows
	if (!glfwInit())
	{
		std::cout << "GLFWInit() failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	TraceMessage("GLFWInit() success");

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

	while (!mainWindow->ShouldClose())// && !secondWindow->ShouldClose()
	{
		deltaTime = glfwGetTime() - lastFrameTime;

		if (deltaTime > expectedTimePerFrame)
		{
			lastFrameTime = glfwGetTime();

			mainWindow->Update();

			ExecuteScreenSaverMovement(mainWindow, deltaTime);
			//secondWindow->Update();
		}
	}

	//secondWindow->ShutDown();
	mainWindow->ShutDown();

	// Terminate GLFW here for multiple windows
	glfwTerminate();

	TraceShutdown();
	return 0;
}

