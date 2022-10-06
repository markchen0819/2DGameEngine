#include <iostream>
#include "GameWindow.h"
#include "Logging.h"
#include "ScreenSaverMovement.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h";
#include <glm/ext/matrix_transform.hpp>
#include "Camera.h"
#include "Node.h"
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/string_cast.hpp>
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
	Vertex v0(glm::vec3(0.0f, 36.60f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
	Vertex v1(glm::vec3(50.0f, -50.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f));
	Vertex v2(glm::vec3(-50.0f, -50.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f));
	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);
	std::vector<Texture> textures;
	textures.push_back(sampleTexture);
	std::vector<unsigned int> indices = { 0, 1, 2 };
	Mesh m(vertices, indices, textures);
	Mesh m2(vertices, indices, textures);

	Transform t(glm::vec3(-50, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

	Node n(t, m, sampleShader);
	// Use this shader
	sampleShader.useProgram();

	// Create camera
	Camera camera(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), mainWindow->Props.Heigth, mainWindow->Props.Width);
	camera.SetupVP(sampleShader); // fix it later

	float val = 0;
	float timeToChangeDir = 1.0f;
	int dir = 1;

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

			// Some math to change rotate, translate, scale
			timeToChangeDir = timeToChangeDir - deltaTime;
			if (timeToChangeDir < 0)
			{
				dir *= -1;
				timeToChangeDir = 1.0f;
			}
			val = val + dir * deltaTime * 5;


			n.shader.useProgram();

			n.transform.SetRotation(0, 0, val );
			n.transform.SetTranslation(-100+ val * 40, -100 + val * 40, 0.0f);
			n.transform.SetScale(1 + val / 10, 1 + val / 10, 1 + val / 10);

			n.Draw();


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

