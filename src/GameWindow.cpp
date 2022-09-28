#include "GameWindow.h"
#include <iostream>


GameWindow::GameWindow() : glfwSuccess(false), pWindow(nullptr), pMonitor(nullptr), shouldClose(false)
{
}

GameWindow::~GameWindow()
{
}


void GameWindow::Init()
{
	// set default props if not initialized
	if (Props.Title.empty())
		Props.Title = "Untitled";

	if (Props.Heigth == 0)
		Props.Heigth = 600;

	if (Props.Width == 0)
		Props.Width = 600;

	// initialize glfw
	if (glfwSuccess)
	{
		std::cout << "GLFW is already initialized!";
		exit(EXIT_FAILURE);
	}

	glfwSetErrorCallback(this->GLFWErrorCallback);
	//if (!glfwInit())
	//	exit(EXIT_FAILURE);
	glfwSuccess = true;

	// Initialize OpenGL Context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

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

	glfwSetWindowSizeCallback(pWindow, this->GLFWWindowSizeCallback);
	glfwSetKeyCallback(pWindow, this->GLFWWindowKeyCallback);
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
	if (!glfwSuccess)
	{
		std::cout << "GLFW  can't shutdown because it has not been initialized yet. Closing program..." << std::endl;
		exit(EXIT_FAILURE);
	}

	glfwDestroyWindow(pWindow);
	//glfwTerminate();
}

bool GameWindow::ShouldClose()
{
	return shouldClose;
}

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
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		int xpos, ypos;
		glfwGetWindowPos(window, &xpos, &ypos);
		glfwSetWindowPos(window, xpos+10, ypos+10);
	}

}


void GameWindow::SetWindowPosition(GLFWwindow* window, int x, int y)
{
	glfwSetWindowPos(window, x, y);
}
