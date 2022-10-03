#include <iostream>
#include "GameWindow.h"
#include "Logging.h"
#include "ScreenSaverMovement.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h";

int main(int argc, char* argv[])
{
	TraceInit();

	// Init GLFW here for multiple windows (prevent multi inits)
	if (!glfwInit())
	{
		std::cout << "GLFWInit() failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	TraceMessage("GLFWInit() success");

	GameWindow* mainWindow = new GameWindow();
	mainWindow->Props.Title = "1stWindow";
	mainWindow->Init();
	mainWindow->SetWindowPosition(50, 50);

	// Experimenting 2nd window
	//GameWindow* secondWindow = new GameWindow();
	//secondWindow->Props.Title = "2ndWindow";
	//secondWindow->Init();


	// Lock FPS
	float FPS = 60;
	float expectedTimePerFrame = 1.0 / FPS;
	float lastFrameTime = glfwGetTime();
	float deltaTime = 0;

	////////////////////Experimenting///////////////////

	// build and compile our shader program
	Shader sampleShader("src/SampleShader.vert", "src/SampleShader.frag");
	Texture sampleTexture("src/Assets/SampleTexture.jpg", "texture_diffuse");

	// Create Mesh
	std::vector<Vertex> vertices;
	Vertex v0(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
	Vertex v1(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f));
	Vertex v2(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f));
	Vertex v3(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f));
	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	std::vector<Texture> textures;
	textures.push_back(sampleTexture);
	std::vector<unsigned int> indices = {
		0, 1, 2, // first triangle
		0, 2, 3
	};
	Mesh m(vertices, textures, indices);

	while (!mainWindow->ShouldClose())// && !secondWindow->ShouldClose()
	{
		deltaTime = glfwGetTime() - lastFrameTime;

		if (deltaTime > expectedTimePerFrame)
		{
			lastFrameTime = glfwGetTime();

			mainWindow->Update();

			//////////////////////////////////////////////////////////////

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			//sampleTexture.activeTextureUnit(0);
			//sampleTexture.bind();
			sampleShader.use(); // put inside Mesh??
			m.Draw(sampleShader);

			//////////////////////////////////////////////////////////////
			
			// swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			mainWindow->SwapBuffers();
			mainWindow->PollEvents();
			// Experimenting 2nd window
			//ExecuteScreenSaverMovement(mainWindow, deltaTime);
			//secondWindow->Update();

		}
	}

	// optional: de-allocate all resources once they've outlived their purpose
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	glActiveTexture(GL_TEXTURE0);
	//////////////////////////////////////////////////////////////

	//secondWindow->ShutDown();
	mainWindow->ShutDown();

	// Terminate GLFW here for multiple windows
	glfwTerminate();

	TraceShutdown();
	return 0;
}

