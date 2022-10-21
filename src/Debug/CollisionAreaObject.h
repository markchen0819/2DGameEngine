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
	void AttachMaterial(Material* m);
	void Draw();

private:
	void SetupObj();
	ShapeType shapeType = ShapeType::NONE;
};


