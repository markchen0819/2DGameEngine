#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform
{
public:

	Transform();
	Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	Transform(const Transform& t);
	~Transform();

	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;
	glm::mat4 model; // final model matrix to print on the screen
	glm::mat4 localModel;

	void SetRotation(const float x, const float y, const float z);
	void SetScale(const float x, const float y, const float z);
	void SetTranslation(const float x, const float y, const float z);

	glm::vec3 GetPosition();
	glm::vec3 GetScale();
	glm::vec3 GetRotation();
	glm::mat4 GetRotationMatrix();
	glm::mat4 GetScaleMatrix();
	glm::mat4 GetTranlateMatrix();

	glm::mat4 getLocalModelMatrix();

	void PrintTransform(); //Debug

private:

	glm::mat4 modelRot, modelScale, modelTrans;
	glm::mat4 createRotationMatrix(const float x, const float y, const float z);
	glm::mat4 createScaleMatrix(const float x, const float y, const float z);
	glm::mat4 createTranslateMatrix(const float x, const float y, const float z);



};