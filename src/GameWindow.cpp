#include "GameWindow.h"
#include <iostream>

GameWindow::GameWindow() : pWindow(nullptr), pMonitor(nullptr), shouldClose(false)
{
}

GameWindow::~GameWindow()
{
}


void GameWindow::Init()
{
	// Error Callbacks
	glfwSetErrorCallback(this->GLFWErrorCallback);


	// Initialize OpenGL Context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	// Create window
	pWindow = glfwCreateWindow(Props.Width, Props.Heigth, Props.Title.c_str(), NULL, NULL);
	if (!pWindow)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(pWindow);
	

	// Initialize glew (or other gl functions loader)
	GLenum glewError = glewInit();
	if (GLEW_OK != glewError)
	{
		std::cout << "Terminating program. Reason:" << std::endl;
		std::cout << "Error in GLEW: " << glewGetErrorString(glewError) << std::endl;
		exit(EXIT_FAILURE);
	}

	// Callbacks
	glfwSetWindowSizeCallback(pWindow, this->GLFWWindowSizeCallback);
	glfwSetKeyCallback(pWindow, this->GLFWWindowKeyCallback);
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
}

void GameWindow::Update()
{
	if (!pWindow)
	{
		std::cout << "Window has not been initialized yet. Closing program..." << std::endl;
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(pWindow);
	// this should not be responsibility of Window. Maybe something like a BufferDraw
	glfwGetFramebufferSize(pWindow, &FrameBuffer.Width, &FrameBuffer.Height);
	glViewport(0, 0, FrameBuffer.Width, FrameBuffer.Height);
	glClear(GL_COLOR_BUFFER_BIT);
	// mkae condition to change color

	glClearColor(1.0, 0.0, 0.0, 1.0);

	glfwPollEvents();
	glfwSwapBuffers(pWindow);

	if (glfwWindowShouldClose(pWindow))
		shouldClose = true;
}

void GameWindow::ShutDown()
{
	if (!pWindow)
	{
		std::cout << "Window can't shutdown because it has not been initialized yet. Closing program..." << std::endl;
		exit(EXIT_FAILURE);
	}
	glfwDestroyWindow(pWindow);
}

bool GameWindow::ShouldClose()
{
	return shouldClose;
}

void GameWindow::SetWindowPosition(int x, int y)
{
	glfwSetWindowPos(pWindow, x, y);
}

std::tuple<int,int> GameWindow :: GetWindowPosition()
{
	int xpos, ypos;
	glfwGetWindowPos(pWindow, &xpos, &ypos);
	return std::make_tuple(xpos, ypos);
}

// Callbacks

void GameWindow::GLFWErrorCallback(int error, const char* description)
{
	std::cout << "Error in GLFW: " << description << std::endl;
}

void GameWindow::GLFWWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	std::cout << "Window being resized... ";
	std::cout << "Width: " << width << " | Height: " << height << std::endl;
}

void GameWindow::GLFWWindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

