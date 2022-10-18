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

	childNodes.clear();
}

void Node::UpdateTransform()
{
	if (parent)
	{
		//std::cout << "Child" << std::endl;
		transform->model = (*parent).transform->getLocalModelMatrix() * transform->getLocalModelMatrix();
		//transform->PrintTransform();
	}
	else
	{
		//std::cout << "Parent" << std::endl;
		transform->model = transform->getLocalModelMatrix();
		//transform->PrintTransform();
	}

}
void Node::Draw()
{
	//transform->Update();
	UpdateTransform();
	material->shader->useProgram();
	material->texture->activeTextureUnit(0);
	material->texture->bindTexture();
	material->shader->setVec4("color", material->color.color);
	material->shader->setMat4("model", transform->model);
	mesh->Draw();

	for (Node* i : childNodes)
	{
		i->Draw();
	}
	material->texture->activeTextureUnit(0);
	glUseProgram(0);
}

void Node::AddChildNode(Node* node)
{
	node->parent = this;
	childNodes.push_back(node);
}
