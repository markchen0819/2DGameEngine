#include "Node.h"

Node::Node(Transform& t, Mesh& m, Shader& s):transform(t), mesh(m), shader(s)
{

}

Node::~Node()
{

}
void Node::Draw()
{
	transform.Update();
	shader.setMat4("model", transform.model);
	mesh.Draw();
}