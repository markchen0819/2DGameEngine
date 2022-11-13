#pragma once

class ObjectFactory
{
public:
	~ObjectFactory();
	static ObjectFactory* GetInstance();

	void CreateAllGameObjects(std::string filename);
	GameObject* CreateGameObject(const rapidjson::Value& thisGobj);
	GameObject* GetGameObjectByName(std::string name);
	void InitializeGameObjects();

	void CreateAllDebugCollisionAreas();

	bool CheckAllGameObjectsInHierachy();
	void SetGameObjectInHierachy(std::string name);

	void AddForDeletion(GameObject* gobj);
	void DeferredDeleteGameObjects();

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

