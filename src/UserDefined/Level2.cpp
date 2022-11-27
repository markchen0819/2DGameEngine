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
	//GameObject* targetObj1 = objectFactory->GetGameObjectByName("Target1");
	//GameObject* targetObj2 = objectFactory->GetGameObjectByName("Target2");
	player->AddComponent<PlayerControlComponent>();
	//targetObj1->AddComponent<SelfRotateComponent>();
	//targetObj2->AddComponent<SelfRotateComponent>();


	GameObject* enemy = CreateEnemy();

	InitializeGameObjects();
	CreateAllDebugCollisionAreas();
	BuildHiearchy("src/Assets/Jsons/Level2/Hierachy.json");

	root.AddChild(enemy);


	SetupCamara(gw);
	// Regiseter UserDefined CollisionEvent
	EventSystem* eventSystem = EventSystem::GetInstance();
	e.SetCallback(Level2CollisionCallback);
	e.SetType(EventType::Collision);
	//eventSystem->AddListener(EventType::Collision, &e);

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

GameObject* Level2::CreateEnemy()
{
	// Create Mesh
	std::vector<glm::vec4> coord;
	coord.push_back(glm::vec4(100.0f, 100.0f, 0.0f, 1.0f));
	coord.push_back(glm::vec4(100.0f, -100.0f, 0.0f, 1.0f));
	coord.push_back(glm::vec4(-100.0f, -100.0f, 0.0f, 1.0f));
	coord.push_back(glm::vec4(-100.0f, 100.0f, 0.0f, 1.0f));
	Vertex v0(coord[0], glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f));
	Vertex v1(coord[1], glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f));
	Vertex v2(coord[2], glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
	Vertex v3(coord[3], glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f));
	std::vector<Vertex> vertices;
	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	std::vector<unsigned int> indices = { 0, 1, 3, 1, 2, 3 };
	Mesh* newMesh = new Mesh(vertices, indices);

	// Create Enemy
	GameObject* enemy = new GameObject();
	enemy->SetName("Enemy");
	enemy->SetMesh(newMesh);
	enemy->SetMaterial(resourceManager->GetMaterialByName("EnemyMaterial"));
	enemy->AddComponent<TransformComponent>();
	enemy->AddComponent<RenderComponent>();
	enemy->AddComponent<PhysicComponent>();
	enemy->AddComponent<EnemyComponent>();
	enemy->Init();


	TransformComponent* tc = enemy->GetComponent<TransformComponent>();
	tc->SetTranslation(0, 250, 0);
	tc->SetScale(0.2, 0.2, 0.2);

	return enemy;
}
GameObject* Level2::CreateStar()
{
	// Create Mesh
	std::vector<glm::vec4> coord;
	coord.push_back(glm::vec4(100.0f, 100.0f, 0.0f, 1.0f));
	coord.push_back(glm::vec4(100.0f, -100.0f, 0.0f, 1.0f));
	coord.push_back(glm::vec4(-100.0f, -100.0f, 0.0f, 1.0f));
	coord.push_back(glm::vec4(-100.0f, 100.0f, 0.0f, 1.0f));
	Vertex v0(coord[0], glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f));
	Vertex v1(coord[1], glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f));
	Vertex v2(coord[2], glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
	Vertex v3(coord[3], glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f));
	std::vector<Vertex> vertices;
	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	std::vector<unsigned int> indices = { 0, 1, 3, 1, 2, 3 };
	Mesh* newMesh = new Mesh(vertices, indices);

	// Create Enemy
	GameObject* star = new GameObject();
	star->SetName("Star");
	star->SetMesh(newMesh);
	star->SetMaterial(resourceManager->GetMaterialByName("EnemyMaterial"));
	star->AddComponent<TransformComponent>();
	star->AddComponent<RenderComponent>();
	star->AddComponent<PhysicComponent>();
	star->Init();

	return star;
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