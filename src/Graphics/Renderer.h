#pragma once
#include <GLEW/include/glew.h>
#include <GLFW/include/GLFW/glfw3.h>
#include <stdlib.h>
#include "../Logging.h"

class Renderer
{
public:

	Renderer();
	~Renderer();

	void InitGLFW();
	void TerminateGLFW();
	void ClearScreen();
	void UnuseShaderProgram();
private:

};

