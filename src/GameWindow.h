#pragma once
#include <glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>;

struct GLFWwindow;
struct GLFWMonitor;

struct WindowProps
{
	int Width = 600;
	int Heigth = 600;
	std::string Title = "Untitled";
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

	void SetWindowPosition(int xpos, int ypos);
	glm::vec2 GetWindowPosition();

private:

	GLFWMonitor* pMonitor;

	// properties
	bool shouldClose;

	// member functions
	static void GLFWErrorCallback(int error, const char* description);
	static void GLFWWindowSizeCallback(GLFWwindow* window, int width, int height);
	static void GLFWWindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
		std::cout << "OpenGL Debug: " << message << std::endl;
	}
};