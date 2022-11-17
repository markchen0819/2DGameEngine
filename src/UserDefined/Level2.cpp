#include "pch.h"


Level2::Level2(std::string name)
{
	TraceMessage(("Level2 ctor " + Name).c_str());
	Name = name;
}

Level2::~Level2()
{
	TraceMessage(("Level2 dtor " + Name).c_str());
}

void Level2::Init(GameWindow* gw)
{
	TraceMessage("---------------------");
	TraceMessage(" Level2::Init");
	TraceMessage("---------------------");
	LoadResources("src/Assets/Jsons/AllResources.json");
	LoadGameObjects("src/Assets/Jsons/AllGameObjects.json");
	ObjectFactory* objectFactory = ObjectFactory::GetInstance();

	// Add User Defined Components // 
	GameObject* player = objectFactory->GetGameObjectByName("Player");
	GameObject* playerChild = objectFactory->GetGameObjectByName("PlayerChild");
	GameObject* targetObj1 = objectFactory->GetGameObjectByName("Target1");
	GameObject* targetObj2 = objectFactory->GetGameObjectByName("Target2");
	player->AddComponent<PlayerControlComponent>();
	targetObj1->AddComponent<SelfRotateComponent>();
	targetObj2->AddComponent<SelfRotateComponent>();

	InitializeGameObjects();
	CreateAllDebugCollisionAreas();
	BuildHiearchy("src/Assets/Jsons/Hierachy.json");
	SetupCamara(gw);

	TraceMessage("---------------------");
	TraceMessage(" Level2::Init finished");
	TraceMessage("---------------------");
}
