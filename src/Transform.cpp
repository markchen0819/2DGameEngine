#include "Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

void Transform::Rotate(float angle, glm::vec3 const& axis_v)
{
	rotation = glm::rotate(rotation, glm::radians(angle), axis_v);
}

void Transform::Scale(glm::vec3 const& v)
{
	scale = glm::scale(scale, v);
}

void Transform::Translate(glm::vec3 const& v)
{
	position = glm::translate(position, v);
}

void Transform::SetPosition(glm::vec3 const& v)
{
	position = glm::mat4
	(v.x, 0.0f, 0.0f, 0.0f,
	 0.0f, v.y, 0.0f, 0.0f,
	 0.0f, 0.0f, v.z, 0.0f,
	 0.0f, 0.0f, 0.0f, 1.0f);
}
void Transform::SetRotation(glm::vec3 const& angles)
{
	int x = glm::radians(angles.x);
	int y = glm::radians(angles.y);
	int z = glm::radians(angles.z);
	rotation = glm::mat4
	(x, 0.0f, 0.0f, 0.0f,
	0.0f, y, 0.0f, 0.0f,
	0.0f, 0.0f, z, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f);
}
void Transform::SetScale(glm::vec3 const& v)
{
	scale = glm::mat4
	(v.x, 0.0f, 0.0f, 0.0f,
		0.0f, v.y, 0.0f, 0.0f,
		0.0f, 0.0f, v.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}