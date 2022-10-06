#include "Transform.h"
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	model = glm::mat4(1.0f);
	modelRot = getRotationMatrix(rotation.x, rotation.y, rotation.z);
	modelScale = getScaleMatrix(scale.x, scale.y, scale.z);
	modelTrans = getTranslateMatrix(position.x, position.y, position.z);
}

Transform::~Transform()
{
}

void Transform::SetRotation(const float x, const float y, const float z)
{
	modelRot = getRotationMatrix(x, y, z);
	Rotation = glm::vec3(x, y, z);
}
void Transform::SetScale(const float x, const float y, const float z)
{
	modelScale = getScaleMatrix(x, y, z);
	Scale = glm::vec3(x, y, z);
}
void Transform::SetTranslation(const float x, const float y, const float z)
{
	modelTrans = getTranslateMatrix(x, y, z);
	Position = glm::vec3(x, y, z);
}

glm::mat4 Transform::getRotationMatrix(const float x, const float y, const float z)
{
	return glm::eulerAngleYXZ(y, x, z); 	// https://glm.g-truc.net/0.9.3/api/a00164.html
}
glm::mat4 Transform::getScaleMatrix(const float x, const float y, const float z)
{
	return glm::mat4{ x,0,0,0,
					  0,y,0,0,
					  0,0,z,0,
					  0,0,0,1 };
}
glm::mat4 Transform::getTranslateMatrix(const float x, const float y, const float z)
{
	return glm::mat4 { 1,0,0,0,
					   0,1,0,0,
		               0,0,1,0,
		               x,y,z,1 };
}
void Transform::PrintTransform()
{
	std::cout << "Position: " << glm::to_string(Position) << std::endl;
	std::cout << "Rotation: " << glm::to_string(Rotation) << std::endl;
	std::cout << "Scale: " << glm::to_string(Scale) << std::endl;
}

void Transform::Update()
{
	model = glm::mat4(1.0f);
	model = modelTrans * modelRot * modelScale * model;

	//PrintTransform();
	//model = modelScale * model;
	//model = modelRot *  model;
	//model = modelTrans * model;
}
