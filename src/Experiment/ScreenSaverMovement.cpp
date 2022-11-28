#include "pch.h"
// Experience code to move window like a screen Saver

static int xDir = 1;
static int yDir = 1;
static int speed = 100; // tweak this for slower, faster movement



void calculateDir(GameWindow* gw)
{
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	int xpos, ypos, width, height;
	glfwGetMonitorWorkarea(monitor, &xpos, &ypos, &width, &height); // 1920 1008

	int x_win, y_win;
	glfwGetWindowPos(gw->pWindow, &x_win, &y_win);

	if (x_win >= (width - gw->Props.Width)) // hit right
	{
		xDir = -1;
	}
	else if (x_win <= 0) // hit left
	{
		xDir = 1;
	}

	if (y_win >= (height - gw->Props.Heigth)) // hit down
	{
		yDir = -1;
	}
	else if (y_win <= 0) // hit up
	{
		yDir = 1;
	}

}

void ExecuteScreenSaverMovement(GameWindow* gw, float deltaTime)
{
	calculateDir(gw);

    glm::vec2 v;
	v = gw->GetWindowPosition();
	gw->SetWindowPosition(v[0] + xDir * deltaTime * speed, v[1] + yDir * deltaTime * speed);

}
