#pragma once
class FrameRateController
{
public:

	~FrameRateController();
	static FrameRateController* GetInstance();

	void SetTargetFrameRate(const float frameRate);
	void FrameStart();
	void FrameEnd();
	double DeltaTime();

private:
	FrameRateController() {}; 
	static FrameRateController* instance;

	double targetFrameRate = 60.0;
	double deltaTime = 0;
	double timeAtFrameStart;
	double timeAtFrameEnd;
	double lastFrameTime;
};

