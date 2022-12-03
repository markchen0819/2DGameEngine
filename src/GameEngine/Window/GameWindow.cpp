#include "pch.h"

GameWindow::GameWindow() : pWindow(nullptr), pMonitor(nullptr), shouldClose(false)
{
	TraceMessage("GameWindow created");
}

GameWindow::~GameWindow()
{
	if (pMonitor != nullptr) delete pMonitor;
}


void GameWindow::Init()
{
	TraceMessage("GameWindow Init()");
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
		TraceMessage("Terminating program. Reason:");
		TraceMessage("Error in GLEW: {}", glewGetErrorString(glewError));
		exit(EXIT_FAILURE);
	}

	// Callbacks
	glfwSetWindowSizeCallback(pWindow, this->GLFWWindowSizeCallback);
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
}

void GameWindow::Update()
{
	if (!pWindow)
	{
		TraceMessage("Window has not been initialized yet. Closing program...");
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(pWindow);
	glfwGetFramebufferSize(pWindow, &FrameBuffer.Width, &FrameBuffer.Height);
	glViewport(0, 0, FrameBuffer.Width, FrameBuffer.Height);

	if (glfwWindowShouldClose(pWindow))
		shouldClose = true;
}

void GameWindow::ShutDown()
{
	TraceMessage("GameWindow ShutDown()");
	if (!pWindow)
	{
		TraceMessage("Window can't shutdown because it has not been initialized yet. Closing program...");
		exit(EXIT_FAILURE);
	}
	glfwDestroyWindow(pWindow);
}

bool GameWindow::ShouldClose()
{
	return shouldClose;
}

void GameWindow::SwapBuffers()
{
	glfwSwapBuffers(pWindow);
}

void GameWindow::PollEvents()
{
	glfwPollEvents();
}

GLFWwindow* GameWindow::GetCurrentContext()
{
	return glfwGetCurrentContext();
}
void GameWindow::SetWindowPosition(int x, int y)
{
	glfwSetWindowPos(pWindow, x, y);
}

glm::vec2 GameWindow::GetWindowPosition()
{
	int xpos, ypos;
	glfwGetWindowPos(pWindow, &xpos, &ypos);
	return glm::vec2 (xpos, ypos);
}

// Callbacks

void GameWindow::RegisterInputCallback(void(*fptr)(GLFWwindow* window, int key, int scancode, int action, int mods))
{
	glfwSetKeyCallback(pWindow, fptr);
}

void GameWindow::GLFWErrorCallback(int error, const char* description)
{
	TraceMessage("Error in GLFW: {}", description);
}

void GameWindow::GLFWWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	TraceMessage("Window being resized... ");
	std::string s = "Width: " + std::to_string(width) + " Height: " + std::to_string(height);
	TraceMessage(s.c_str());
}


