#include "pch.h"

Transform::Transform() :
	model(glm::mat4(1.0f)), localModel(glm::mat4(1.0f)),
	modelRot(glm::mat4(1.0f)), modelScale(glm::mat4(1.0f)), modelTrans(glm::mat4(1.0f)),
	Position(glm::vec3(0.0f, 0.0f, 0.0f)),
	Rotation(glm::vec3(0.0f, 0.0f, 0.0f)),
	Scale(glm::vec3(1.0f, 1.0f, 1.0f))
{ }
Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	SetRotation(rotation.x, rotation.y, rotation.z);
	SetScale(scale.x, scale.y, scale.z);
	SetTranslation(position.x, position.y, position.z);
	model = modelTrans * modelRot * modelScale * glm::mat4(1.0f);
	localModel = model;
}
Transform::Transform(const Transform& t) :
	model(t.model), localModel(t.localModel),
	modelRot(t.modelRot), modelScale(t.modelScale), modelTrans(t.modelTrans),
	Position(t.Position), Rotation(t.Rotation), Scale(t.Scale)
{ }
Transform::~Transform() {}

void Transform::operator=(const Transform& t)
{
	model = t.model;
	localModel = t.localModel;
	modelRot = t.modelRot;
	modelScale = t.modelScale;
	modelTrans = t.modelTrans;
	Position = t.Position;
	Rotation = t.Rotation;
	Scale = t.Scale;
}

void Transform::SetRotation(const float x, const float y, const float z)
{
	modelRot = createRotationMatrix(x, y, z);
	Rotation = glm::vec3(x, y, z);
}
void Transform::SetScale(const float x, const float y, const float z)
{
	modelScale = createScaleMatrix(x, y, z);
	Scale = glm::vec3(x, y, z);
}
void Transform::SetTranslation(const float x, const float y, const float z)
{
	modelTrans = createTranslateMatrix(x, y, z);
	Position = glm::vec3(x, y, z);
}

glm::vec3 Transform::GetPosition() { return Position; }
glm::vec3 Transform::GetScale() { return Scale; }
glm::vec3 Transform::GetRotation() { return Rotation; }
glm::mat4 Transform::GetRotationMatrix() { return modelRot; }
glm::mat4 Transform::GetScaleMatrix() { return modelScale; }
glm::mat4 Transform::GetTranlateMatrix() { return modelTrans; }

glm::mat4 Transform::getLocalModelMatrix()
{
	localModel = modelTrans * modelRot * modelScale * glm::mat4(1.0f);
	return localModel;
}

void Transform::PrintTransform()
{
	std::cout << "Position: " << glm::to_string(Position) << std::endl;
	std::cout << "Rotation: " << glm::to_string(Rotation) << std::endl;
	std::cout << "Scale: " << glm::to_string(Scale) << std::endl;
}

glm::mat4 Transform::createRotationMatrix(const float x, const float y, const float z)
{
	return glm::eulerAngleYXZ(glm::radians(y), glm::radians(x), glm::radians(z)); 	// https://glm.g-truc.net/0.9.3/api/a00164.html
}
glm::mat4 Transform::createScaleMatrix(const float x, const float y, const float z)
{
	return glm::mat4{ x,0,0,0,
					  0,y,0,0,
					  0,0,z,0,
					  0,0,0,1 };
}
glm::mat4 Transform::createTranslateMatrix(const float x, const float y, const float z)
{
	return glm::mat4{ 1,0,0,0,
					   0,1,0,0,
					   0,0,1,0,
					   x,y,z,1 };
}





