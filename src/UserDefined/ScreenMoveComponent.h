#pragma once
class ScreenMoveComponent : public Component
{
public:
	ScreenMoveComponent() {};
	~ScreenMoveComponent() {};

	virtual void Init();
	virtual void Update();
	virtual void Destroy();

private:
	GameWindow* gameWindow;
	GLFWmonitor* monitor;
	int xpos, ypos, width, height;
	int xDir = 1;
	int yDir = 1;
	int speed = 100;
	void calculateDirection();
};

