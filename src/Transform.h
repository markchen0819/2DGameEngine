#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform
{
public:

	Transform();
	~Transform();

	glm::mat4 position;
	glm::mat4 rotation;
	glm::mat4 scale;


	void Rotate(float angle, glm::vec3 const& axis_v);
	void Scale(glm::vec3 const& v);
	void Translate(glm::vec3 const& v);

	void SetPosition(glm::vec3 const& v);
	void SetRotation(glm::vec3 const& angles);
	void SetScale(glm::vec3 const& v);


private:

};