#pragma once
#include "GameWindow.h"
#include <array>


enum Input
{
	RIGHT,
	LEFT,
	DOWN,
	UP,
	DEFAULTINPUT
};

enum InputState
{
	PRESSED,
	RELEASED,
	HOLD,
	DEFAULTINPUTSTATE
};

class InputManager
{
public:

	~InputManager();
	static InputManager* GetInstance();
	void Init(GameWindow* gamewindow);

	void PollEvents();

	bool IsKeyUp(Input input);
	bool IsKeyDown(Input input);
	bool IsKeyPressed(Input input);

private:

	InputManager() {}; // Private constructor so that no objects can be created.
	static InputManager* instance;
	GameWindow* gameWindow=nullptr; //In case of multiple windows, store the main one.

	//static Input mapInput(int glfwKey);
	//static InputState mapInputState(int glfwKeyState);
	void UpdateInputStates();
	static void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	std::array<bool, 4> currentInputStates = {};
	std::array<bool, 4> isCurPressed;
	std::array<bool, 4> isCurReleased;
	std::array<bool, 4> isPrevPressed;
	std::array<bool, 4> isPrevReleased;

};

