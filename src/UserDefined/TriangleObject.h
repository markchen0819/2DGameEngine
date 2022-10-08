#pragma once
#include "../Node.h"

class TriangleObject : public Node
{
public:
	TriangleObject();
	~TriangleObject();

	void AttachMaterial(Material* m);
	void Draw();

private:
	void SetupTransform();
	void SetupMesh();

};

