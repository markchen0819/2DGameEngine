#include "Camera.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 lookAtTarget, float const height, float const width)
{
	this->position = position;

	projection = glm::mat4(1.0f);
	view = glm::mat4(1.0f);
	float h = height / 2;
	float w = width / 2;
	projection = glm::ortho(-h, h, -w, w, 0.0f, 100.0f);
	view = glm::lookAt(position, lookAtTarget, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::SetShaderVP(Shader& shader)
{
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
}