#include "Node.h"

Node::Node()
{

}

Node::Node(Transform t, Mesh m, Material* mat)
{
	transform = new Transform(t);
	mesh = new Mesh(m);
	material = mat;
}

Node::~Node()
{
	if (transform)
	{
		delete transform;
	}
	if (mesh)
	{
		delete mesh;
	}
}
void Node::Draw()
{
	transform->Update();
	material->texture->activeTextureUnit(0);
	material->texture->bindTexture();
	material->shader->setVec4("color", material->color.color);
	material->shader->setMat4("model", transform->model);
	mesh->Draw();
}