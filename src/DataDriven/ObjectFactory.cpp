#include "pch.h"

ObjectFactory* ObjectFactory::instance = nullptr;
ObjectFactory* ObjectFactory::GetInstance()
{
	static ObjectFactory* instance = new ObjectFactory();
	return instance;
}
ObjectFactory::~ObjectFactory()
{
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
		gameobjectsInHierachy[temp->GetName()] = false;
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

void ObjectFactory::CreateAllDebugCollisionAreas()
{
	TraceMessage("---CreateAllDebugCollisionAreas---");
	for (std::unordered_map<std::string, GameObject*>::iterator itr = gameobjects.begin();
		itr != gameobjects.end(); itr++)
	{
		GameObject* thisGobj = itr->second;
		TraceMessage(thisGobj->GetName().c_str());
		PhysicComponent* pc = thisGobj->GetComponent<PhysicComponent>();
		if (pc != nullptr)
		{
			CollisionAreaObject* cao = new CollisionAreaObject();
			(*cao).SetName((thisGobj->GetName()+"_Collision Area").c_str());
			(*cao).SetMaterial(ResourceManager::GetInstance()->GetMaterialByName("CollisionMaterial"));
			TraceMessage((thisGobj->GetName() + "_Collision Area").c_str());

			CollisionShape* cs = pc->GetBody()->GetCollisionShape();
			ShapeType st = cs->Type;
			if (st == ShapeType::OBB)
			{
				CollisionOBB* obb = dynamic_cast<CollisionOBB*>(cs);
				(*cao).SetMesh(obb->verticies);
			}
			else if (st == ShapeType::AABB)
			{
				//TO:DO
				//(*cao).SetMesh(r,l,u,d);
			}
			else if (st == ShapeType::CIRCLE)
			{
				//TO:DO
				//(*cao).SetMesh(radius);
			}
			thisGobj->AddChild(cao);
		}
		else
		{
			TraceMessage("No physic component, collision shape not generated");
		}
	}
}


// Make sure all created objects are added to the scene hierachy
bool ObjectFactory::CheckAllGameObjectsInHierachy()
{
	for (std::unordered_map<std::string, bool>::iterator itr = gameobjectsInHierachy.begin();
		itr != gameobjectsInHierachy.end(); itr++)
	{
		if (itr->second == false)
		{
			TraceMessage((itr->first+ " is not in hierachy, potential leak!").c_str());
			exit(EXIT_FAILURE);
			return false;
		}
	}
	TraceMessage("All created objects are added to hierachy");
	return true;
}

void ObjectFactory::SetGameObjectInHierachy(std::string name)
{
	gameobjectsInHierachy[name] = true;
}

// Deletion is not restricted to gobjs generated by the factory but anywhere
void ObjectFactory::AddForDeletion(GameObject* gobj)
{
	gameObjectsToDelete.push_back(gobj);
}
void ObjectFactory::DeferredDeleteGameObjects()
{
	for (GameObject* gobj : gameObjectsToDelete)
	{
		gameobjects.erase(gobj->GetName());
		gobj->Destroy();
		delete gobj;
		gobj = nullptr;
	}
	gameObjectsToDelete.clear();
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

