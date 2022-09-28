#pragma once


#include <glew.h>
#include <GLFW/glfw3.h>
#include <string>


struct GLFWwindow;
struct GLFWMonitor;

struct WindowProps
{
	int Width = 0;
	int Heigth = 0;
	std::string Title;
};

struct FrameBufferProps
{
	int Width = 0;
	int Height = 0;
};

class GameWindow
{
public:
	GameWindow();
	~GameWindow();
	WindowProps Props;
	FrameBufferProps FrameBuffer;
	GLFWwindow* pWindow;

	void Init();
	void Update();
	void ShutDown();
	bool ShouldClose();

	void SetWindowPosition(GLFWwindow* window, int xpos, int ypos);

private:


	// GameWindow pointers
	//GLFWwindow* pWindow;
	GLFWMonitor* pMonitor;

	// glfw setup
	bool glfwSuccess;

	// properties
	bool shouldClose;

	// member functions
	static void GLFWErrorCallback(int error, const char* description);
	static void GLFWWindowSizeCallback(GLFWwindow* window, int width, int height);
	static void GLFWWindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};