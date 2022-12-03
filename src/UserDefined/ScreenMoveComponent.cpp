#include "pch.h"

void ScreenMoveComponent::Init()
{
	gameWindow = GameEngine::GetInstance()->GetMainWindow();
	monitor = glfwGetPrimaryMonitor();
	glfwGetMonitorWorkarea(monitor, &xpos, &ypos, &width, &height); // 1920 1008
}

void ScreenMoveComponent::Update()
{
	float deltaTime = FrameRateController::GetInstance()->DeltaTime();
	calculateDirection();
	glm::vec2 v;
	v = gameWindow->GetWindowPosition();
	gameWindow->SetWindowPosition(v[0] + xDir * deltaTime * speed, v[1] + yDir * deltaTime * speed);

}

void ScreenMoveComponent::Destroy()
{
	gameWindow->SetWindowPosition(width / 2 - gameWindow->Props.Width / 2, height / 2 - gameWindow->Props.Heigth / 2);
}

void ScreenMoveComponent::calculateDirection()
{
	int x_win, y_win;
	glfwGetWindowPos(gameWindow->pWindow, &x_win, &y_win);

	if (x_win >= (width - gameWindow->Props.Width)) // hit right
	{
		xDir = -1;
	}
	else if (x_win <= 0) // hit left
	{
		xDir = 1;
	}

	if (y_win >= (height - gameWindow->Props.Heigth)) // hit down
	{
		yDir = -1;
	}
	else if (y_win <= 0) // hit up
	{
		yDir = 1;
	}
}
