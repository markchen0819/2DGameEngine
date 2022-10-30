#include "../pch.h"

Renderer* Renderer::instance = nullptr;
Renderer* Renderer::GetInstance()
{
	static Renderer* instance = new Renderer();
	return instance;
}
Renderer::~Renderer()
{
	delete instance;
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
void Renderer::Draw(std::string Name, Transform* transform, Mesh* mesh, Material* material)
{
	if (material == nullptr)
	{
		std::string s = "Error: Node [" + Name + "] has not attached a material";
		TraceMessage(s.c_str());
		return;
	}
	material->shader->useProgram();
	material->texture->activeTextureUnit(0);
	material->texture->bindTexture();
	material->shader->setVec4("color", material->color.color);
	material->shader->setMat4("model", transform->model);
	mesh->Draw();
	material->texture->activeTextureUnit(0);
	glUseProgram(0);
}

void Renderer::UpdateModelMatrix(Node* parent, Transform* transform)
{
	if (parent)
	{
		//std::cout << "Child" << std::endl;
		transform->model = parent->transform->getLocalModelMatrix() * transform->getLocalModelMatrix();
		//transform->PrintTransform();
	}
	else
	{
		//std::cout << "Parent" << std::endl;
		transform->model = transform->getLocalModelMatrix();
		//transform->PrintTransform();
	}
}
