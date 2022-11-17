#pragma once

class RenderComponent : public Component
{
public:
	RenderComponent();
	~RenderComponent();

	virtual void Init();
	virtual void Update();
	virtual void Destroy();
	//virtual void HandleEvent(void* eventData);

	void Draw();
	void SetMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	Mesh* GetMesh();
	Material* GetMaterial();

	virtual void Serialize();
	virtual void Deserialize(const rapidjson::Value& obj);

private:

};

