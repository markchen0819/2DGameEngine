#pragma once

class Renderer
{
public:
	~Renderer();
	static Renderer* GetInstance();

	void InitGLFW();
	void TerminateGLFW();
	void ClearScreen();
	void UnuseShaderProgram();
	void Draw(std::string Name, Transform* transform, Mesh* mesh, Material* material);
	void UpdateModelMatrix(Node* parent, Transform* transform);
private:
	Renderer() {};
	static Renderer* instance;
};

