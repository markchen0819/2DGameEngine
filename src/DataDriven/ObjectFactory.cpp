#include "pch.h"

ObjectFactory* ObjectFactory::instance = nullptr;
ObjectFactory* ObjectFactory::GetInstance()
{
	static ObjectFactory* instance = new ObjectFactory();
	return instance;
}
ObjectFactory::~ObjectFactory()
{
	for (std::unordered_map<std::string, GameObject*>::iterator itr = gameobjects.begin();
		itr != gameobjects.end(); itr++)
	{
		delete itr->second;
	}
	delete instance;
}

void ObjectFactory::CreateAllGameObjects(std::string filename)
{
	TraceMessage("---CreateGameObjects---");
	OpenFileAndGetDoc(filename);
	rapidjson::Value& gobjsInJson = doc.FindMember(JSONConstants::GAMEOBJECTS)->value;
	for (rapidjson::Value::ConstMemberIterator itr = gobjsInJson.MemberBegin(); itr != gobjsInJson.MemberEnd(); ++itr)
	{
		const rapidjson::Value& thisGobj = itr->value;
		GameObject* temp = CreateGameObject(thisGobj);
		gameobjects[temp->GetName()] = temp;
	}
	CloseFile();

}
GameObject* ObjectFactory::CreateGameObject(const rapidjson::Value& thisGobj)
{

	GameObject* temp = new GameObject();
	std::string name_str = thisGobj.FindMember(JSONConstants::GAMEOBJECT_NAME)->value.GetString();
	std::string mat_str = thisGobj.FindMember(JSONConstants::MATERIAL)->value.GetString();
	temp->SetName(name_str);
	temp->SetMaterial(ResourceManager::GetInstance()->GetMaterialByName(mat_str));
	TraceMessage(name_str.c_str());
	
	const rapidjson::Value& components = thisGobj.FindMember(JSONConstants::COMPONENTS)->value;
	for (rapidjson::Value::ConstMemberIterator itr = components.MemberBegin(); itr != components.MemberEnd(); ++itr)
	{
		std::string componentType = itr->name.GetString();
		if (componentType == JSONConstants::TRANSFORM_COMPONENT)
		{
			const rapidjson::Value& componentMembers = itr->value;
			temp->AddComponent<TransformComponent>();
			temp->GetComponent<TransformComponent>()->Deserialize(componentMembers);
		}
		else if (componentType == JSONConstants::RENDER_COMPONENT)
		{
			const rapidjson::Value& componentMembers = itr->value;
			temp->AddComponent<RenderComponent>();
			temp->GetComponent<RenderComponent>()->Deserialize(componentMembers);
		}
		else if (componentType == JSONConstants::PHYSIC_COMPONENT)
		{
			const rapidjson::Value& componentMembers = itr->value;
			temp->AddComponent<PhysicComponent>();
			temp->GetComponent<PhysicComponent>()->Deserialize(componentMembers);
		}
	}
	return temp;
}


GameObject* ObjectFactory::GetGameObjectByName(std::string name)
{
	if (gameobjects.find(name) != gameobjects.end())
	{
		return  gameobjects[name];
	}
	std::string str ="GameObject not found in ObjectFactory : " + name;
	TraceMessage(str.c_str());
	exit(EXIT_FAILURE);
}

void ObjectFactory::InitializeGameObjects()
{
	for (std::unordered_map<std::string, GameObject*>::iterator itr = gameobjects.begin();
		itr != gameobjects.end(); itr++)
	{
		itr->second->Init();
	}
}


// helpers
void ObjectFactory::OpenFileAndGetDoc(std::string filename)
{
	fopen_s(&fp, filename.c_str(), "rb");
	if (!fp)
	{
		std::string str = "File not found: " + filename;
		TraceMessage(str.c_str());
		exit(EXIT_FAILURE);
	}
	char readBuffer[8192];
	rapidjson::FileReadStream inputStream(fp, readBuffer, sizeof(readBuffer));
	doc.ParseStream(inputStream);
}
void ObjectFactory::CloseFile()
{
	fclose(fp);
}

