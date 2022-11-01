#pragma once

class CollisionAreaObject : public Node
{
public:
	CollisionAreaObject();
	~CollisionAreaObject();

	virtual void Init();
	virtual void Update();
	virtual void Destroy();
	//virtual void HandleEvent(void* eventData);
	virtual void Draw();

	void UpdateTransform(Transform t);
	void SetMesh(float radius);
	void SetMesh(float r, float l, float u, float d);
	void SetMesh(std::vector<glm::vec4> v);

	void SetMaterial(Material* m);

private:

	ShapeType shapeType = ShapeType::NONE;
	void SetDefaultShape();

};


