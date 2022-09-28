#include <iostream>
#include "GameWindow.h"
#include "Logging.h"

void calculateDir(GameWindow* gw, int& x, int& y)
{
	//GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	//int xpos, ypos, width, height;
	//glfwGetMonitorWorkarea(monitor, &xpos, &ypos, &width, &height); // 1920 /1008

	int x_win, y_win;
	glfwGetWindowPos(gw->pWindow, &x_win, &y_win);

	if (x_win >= (1920-600)) // hit right
	{
		x = -1;
	}
	else if (x_win <= 0) // hit left
	{
		x = 1;
	}
	
	if (y_win >= (1080-600) ) // hit down
	{
		y = -1;
	}
	else if (y_win <= 0) // hit up
	{
		y = 1;
	}

}
int main(int argc, char* argv[])
{
	TraceInit();

	if (!glfwInit())
		exit(EXIT_FAILURE);

	GameWindow* mainWindow = new GameWindow();
	mainWindow->Props.Title = "1stWindow";
	mainWindow->Init();

	//GameWindow* secondWindow = new GameWindow();
	//secondWindow->Props.Title = "2ndWindow";
	//secondWindow->Init();

	// Main loop
	// FPS
	//https://stackoverflow.com/questions/41742142/limiting-fps-in-c
	float FPS = 60;
	float maxPeriod = 1.0 / FPS;
	float lastFrameTime = glfwGetTime();
	float deltaTime = 0;

	int x = 1, y = 1;
	mainWindow->SetWindowPosition(mainWindow->pWindow, 50, 50);
	while (!mainWindow->ShouldClose() )// && !secondWindow->ShouldClose()
	{
		deltaTime = glfwGetTime() - lastFrameTime;

		if (deltaTime > maxPeriod)
		{
			lastFrameTime = glfwGetTime();
			// how to delay?

			mainWindow->Update();
			calculateDir(mainWindow, x, y);

			int xpos, ypos;
			glfwGetWindowPos(mainWindow->pWindow, &xpos, &ypos);

			mainWindow->SetWindowPosition(mainWindow->pWindow, xpos + x * deltaTime * 300, ypos + y * deltaTime * 300);
			//secondWindow->Update();
		}

	}

	//secondWindow->ShutDown();
	mainWindow->ShutDown();

	glfwTerminate();
	TraceShutdown();
	return 0;
}

