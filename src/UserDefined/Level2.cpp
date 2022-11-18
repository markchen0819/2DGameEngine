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

void Level2CollisionCallback(void* eventData);
void Level2::Init(GameWindow* gw)
{
	TraceMessage("---------------------");
	TraceMessage("Level2::Init");
	TraceMessage("---------------------");
	LoadResources("src/Assets/Jsons/Level2/Resources.json");
	LoadGameObjects("src/Assets/Jsons/Level2/GameObjects.json");

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
	BuildHiearchy("src/Assets/Jsons/Level2/Hierachy.json");
	SetupCamara(gw);

	// Regiseter UserDefined CollisionEvent
	EventSystem* eventSystem = EventSystem::GetInstance();
	e.SetCallback(Level2CollisionCallback);
	e.SetType(EventType::Collision);
	eventSystem->AddListener(EventType::Collision, &e);

	TraceMessage("---------------------");
	TraceMessage("Level2::Init finished");
	TraceMessage("---------------------");
}

void Level2::Update()
{
	if (!isRunning) return;
	//ExecuteScreenSaverMovement(GameEngine::GetInstance()->GetMainWindow(), FrameRateController::GetInstance()->DeltaTime());
	Scene::Update();
}

// Event Callbacks for engine
void Level2CollisionCallback(void* eventData)
{
	CollisionEvent* converted = static_cast<CollisionEvent*>(eventData);
	if (converted)
	{
		// Delete non player
		if (converted->gobj1->GetName() != "Player")
		{
			converted->gobj1->SetAlive(false);
			converted->gobj1->SetToBeDeleted();
		}
		if (converted->gobj2->GetName() != "Player")
		{
			converted->gobj2->SetAlive(false);
			converted->gobj2->SetToBeDeleted();
		}
	}

}