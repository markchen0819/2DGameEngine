#pragma once
#include "../Graphics/Node.h"
#include "../Physics/ShapeType.h"
class CollisionAreaObject : public Node
{
public:
	CollisionAreaObject();
	~CollisionAreaObject();

	void UpdateTransform(Transform t);
	void SetMesh(float radius);
	void SetMesh(float r, float l, float u, float d);
	void SetMesh(std::vector<glm::vec4> v);

	void SetName(std::string s);
	void Draw();
	void AttachMaterial(Material* m);
private:

	ShapeType shapeType = ShapeType::NONE;

	Material collisionMaterial;
	Shader* collisionShader; 
	Texture* collisionTexture; 
	void SetDefaultShape();

};


