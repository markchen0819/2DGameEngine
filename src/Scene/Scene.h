#pragma once
class Scene
{

public:
	Scene();
	~Scene();

	void LoadResources(std::string filename);
	void LoadGameObjects(std::string filename);
	void BuildHiearchy(std::string filename);
	void SetupCamara(GameWindow* window);
	void DeferredDeleteGameObject();

	void Update();
	void LateUpdate();
	void Draw();
	void Destroy();

	GameObject* GetGameObjectByName(std::string name);

private:

	Root root;
	ResourceManager* resourceManager; // aggregation
	ObjectFactory* objectFactory; // aggregation
	PhysicsManager* physicsManager; // aggregation

	void recursiveBuildHierachy(rapidjson::Value::ConstMemberIterator nodeIterator, Node* parent);
};

