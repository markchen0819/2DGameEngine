#pragma once

enum Input
{
	RIGHT,
	LEFT,
	DOWN,
	UP,
	ENTER,
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

	std::array<bool, 5> currentInputStates = {};
	std::array<bool, 5> isCurPressed;
	std::array<bool, 5> isCurReleased;
	std::array<bool, 5> isPrevPressed;
	std::array<bool, 5> isPrevReleased;

};

