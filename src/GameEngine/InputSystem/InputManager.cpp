#include "pch.h"

InputManager* InputManager::instance = nullptr;
InputManager* InputManager::GetInstance()
{
	static InputManager* instance = new InputManager();
	return instance;
}
InputManager::~InputManager()
{
	delete instance;
}


void InputManager::Init(GameWindow* gameWindow)
{
	this->gameWindow = gameWindow;
	gameWindow->RegisterInputCallback(this->GLFWKeyCallback);

	for (int i = 0; i < currentInputStates.size(); ++i)
	{
		isCurPressed[i] = false;
		isCurReleased[i] = true;
		isPrevPressed[i] = false;
		isPrevReleased[i] = true;
	}
	std::string temp = "InputManger registers GameWindow: " + gameWindow->Props.Title;
	TraceMessage(temp.c_str());
}

void InputManager::GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}


void InputManager::UpdateInputStates()
{
	GLFWwindow* pWindow = this->gameWindow->pWindow;
	currentInputStates[Input::RIGHT] = glfwGetKey(pWindow, GLFW_KEY_RIGHT);
	currentInputStates[Input::LEFT] = glfwGetKey(pWindow, GLFW_KEY_LEFT);
	currentInputStates[Input::DOWN] = glfwGetKey(pWindow, GLFW_KEY_DOWN);
	currentInputStates[Input::UP] = glfwGetKey(pWindow, GLFW_KEY_UP);
	currentInputStates[Input::ENTER] = glfwGetKey(pWindow, GLFW_KEY_ENTER);

	// iterate if the key is pressed or release
	for (int i = 0; i < currentInputStates.size(); ++i)
	{
		isPrevPressed[i] = isCurPressed[i];
		isPrevReleased[i] = isCurReleased[i];

		if (currentInputStates[i])
		{
			isCurPressed[i] = true;
			isCurReleased[i] = false;
		}
		else
		{
			isCurPressed[i] = false;
			isCurReleased[i] = true;
		}
	}

}

void InputManager::PollEvents()
{
	UpdateInputStates();
}


bool InputManager::IsKeyUp(Input input)
{
	return !currentInputStates[(int)input];
}

bool InputManager::IsKeyDown(Input input)
{
	return currentInputStates[(int)input];
}

bool InputManager::IsKeyPressed(Input input) // Down and then up immediately
{
	return (isCurPressed[(int)input] && !isPrevPressed[(int)input]);
}



// UnUsed Yet
//Input InputManager::mapInput(int glfwKey)
//{
//	switch (glfwKey)
//	{
//	case GLFW_KEY_RIGHT: return Input::RIGHT;
//	case GLFW_KEY_LEFT: return Input::LEFT;
//	case GLFW_KEY_DOWN: return Input::DOWN;
//	case GLFW_KEY_UP: return Input::UP;
//	default: return Input::DEFAULTINPUT;
//	}
//}
//InputState InputManager::mapInputState(int glfwKeyState)
//{
//	switch (glfwKeyState)
//	{
//	case GLFW_PRESS: return InputState::PRESSED;
//	case GLFW_RELEASE: return InputState::RELEASED;
//	default: return InputState::DEFAULTINPUTSTATE;
//	}
//}
//

