#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform
{
public:

	Transform();
	Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	Transform(Transform& t);
	~Transform();

	glm::mat4 model; // final model matrix to print on the screen
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;

	void SetRotation(const float x, const float y, const float z);
	void SetScale(const float x, const float y, const float z);
	void SetTranslation(const float x, const float y, const float z);

	glm::mat4 getRotationMatrix(const float x, const float y, const float z);
	glm::mat4 getScaleMatrix(const float x, const float y, const float z);
	glm::mat4 getTranslateMatrix(const float x, const float y, const float z);
	glm::mat4 getLocalModelMatrix();

	void Update();// Maybe can take this out after Scene graph
	void PrintTransform(); //Debug

private:
	glm::mat4 modelRot, modelScale, modelTrans;

};