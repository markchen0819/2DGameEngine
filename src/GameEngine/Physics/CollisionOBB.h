#pragma once

class CollisionOBB : public CollisionShape
{
public:
	CollisionOBB();
	CollisionOBB(std::vector<glm::vec4> v);
	~CollisionOBB();

	std::vector<glm::vec4> verticies;
	// In world coords when init! not relative to shape! Remember to calculate or support in the future

	glm::vec4 GetCenter();
	void SetCenter(glm::vec4 c);

	glm::mat4 GetRotationMat();
	void SetRotation(glm::vec4 r);

private:
	glm::vec4 center;
	glm::mat4 rotation;

};

