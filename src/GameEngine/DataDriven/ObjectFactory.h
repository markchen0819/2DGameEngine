#pragma once

class ObjectFactory
{
public:
	~ObjectFactory();
	static ObjectFactory* GetInstance();

	// 1. Create GameObjects on scene load
	void CreateAllGameObjects(std::string filename);
	GameObject* CreateGameObject(const rapidjson::Value& thisGobj);
	GameObject* GetGameObjectByName(std::string name);
	void InitializeGameObjects();
	void CreateAllDebugCollisionAreas();

	// 2. Make sure added to scene hiearchy, factory has no responsibility for these objs anymore
	void SetGameObjectInHierachy(std::string name);
	bool CheckAllGameObjectsInHierachy();

	// 3. Helper for deferred deletion
	void AddForDeletion(GameObject* gobj);
	void DeferredDeleteGameObjects();
	std::vector<GameObject*> GetGameObjectsToDeleteVector();

private:
	ObjectFactory() {};
	static ObjectFactory* instance;

	std::unordered_map<std::string, GameObject*> gameobjects;
	std::unordered_map<std::string, bool> gameobjectsInHierachy;
	std::vector<GameObject*> gameObjectsToDelete;

	FILE* fp = nullptr;
	rapidjson::Document doc;
	void OpenFileAndGetDoc(std::string filename);
	void CloseFile();
};

