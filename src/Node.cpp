#include "Node.h"

Node::Node(Transform t, Mesh m, Shader& s, glm::vec4 c):transform(t), mesh(m), shader(s), color(c)
{

}

Node::~Node()
{

}
void Node::Draw()
{
	transform.Update();
	shader.setVec4("color", color);
	shader.setMat4("model", transform.model);
	mesh.Draw();
}