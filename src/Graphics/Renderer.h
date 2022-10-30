#pragma once
#include <stdlib.h>
#include <string>
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"
#include "Node.h"
#include "../Logging.h"

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

