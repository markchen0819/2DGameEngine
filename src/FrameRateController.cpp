#include "pch.h"
FrameRateController* FrameRateController::instance = nullptr;
FrameRateController* FrameRateController::GetInstance()
{
	static FrameRateController* instance = new FrameRateController();
	return instance;
}
FrameRateController::~FrameRateController()
{
	delete instance;
}


void FrameRateController::SetTargetFrameRate(const float frameRate)
{
	targetFrameRate = frameRate;
}
void FrameRateController::FrameStart()
{
	timeAtFrameStart = glfwGetTime();
}
void FrameRateController::FrameEnd()
{
	timeAtFrameEnd = glfwGetTime();
	double expectedTimePerFrame = 1 / targetFrameRate;
	while ((timeAtFrameEnd - timeAtFrameStart) < expectedTimePerFrame)
	{
		timeAtFrameEnd = glfwGetTime();
	}
	lastFrameTime = timeAtFrameEnd - timeAtFrameStart;
	deltaTime = lastFrameTime;
}

double FrameRateController::DeltaTime()
{
	return deltaTime;
}