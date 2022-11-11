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

private:
	ObjectFactory() {};
	static ObjectFactory* instance;

	std::unordered_map<std::string, GameObject*> gameobjects;

	FILE* fp = nullptr;
	rapidjson::Document doc;
	void OpenFileAndGetDoc(std::string filename);
	void CloseFile();
};

