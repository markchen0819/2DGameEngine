#include "GameObject.h"
#include "Shader.h"

GameObject::GameObject(Transform t, Mesh m) :transform(t), mesh(m)
{

}
GameObject::~GameObject()
{

}

void GameObject::Draw(glm::mat4 model, Shader& shader)
{
	//shader.setMat4("model", model);
	mesh.Draw();
}