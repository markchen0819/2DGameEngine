#include "pch.h"

Level1::Level1(std::string name)
{
	TraceMessage(("Level1 ctor " + Name).c_str());
	Name = name;
}

Level1::~Level1()
{
	TraceMessage(("Level1 dtor " + Name).c_str());
}

void Level1::Init(GameWindow* gw)
{
	TraceMessage("---------------------");
	TraceMessage("Level1::Init");
	TraceMessage("---------------------");
	LoadResources("src/Assets/Jsons/Level1/Resources.json");
	LoadGameObjects("src/Assets/Jsons/Level1/GameObjects.json");

	// Add User Defined Components // 
	GameObject* picture = objectFactory->GetGameObjectByName("Picture");
	picture->AddComponent<PressEnterToNextScreenComponent>();

	InitializeGameObjects();
	CreateAllDebugCollisionAreas();
	BuildHiearchy("src/Assets/Jsons/Level1/Hierachy.json");
	SetupCamara(gw);

	TraceMessage("---------------------");
	TraceMessage("Level1::Init finished");
	TraceMessage("---------------------");
}


void Level1::Update()
{
	Scene::Update();
}
