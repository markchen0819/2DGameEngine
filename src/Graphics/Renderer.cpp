#include "Renderer.h"
#include <iostream>



Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::InitGLFW()
{
	// Init GLFW here for multiple windows (prevent multi inits)
	if (!glfwInit())
	{
		std::cout << "GLFWInit() failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	TraceMessage("GLFWInit() success");
}

void Renderer::TerminateGLFW()
{
	glfwTerminate();
}

void Renderer::ClearScreen()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::UnuseShaderProgram()
{
	glUseProgram(0);
}
