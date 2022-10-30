#pragma once
#include <glm/glm.hpp>
#include "Graphics/Shader.h"

class Camera
{
public:
	glm::vec3 position;
	glm::mat4 projection;
	glm::mat4 view;

	Camera(glm::vec3 position, glm::vec3 lookAtTarget, float const height, float const width);
	void SetShaderVP(Shader& shader);

};

