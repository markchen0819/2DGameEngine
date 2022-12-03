#include "pch.h"

int Level2::Score = 0;

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
	TraceMessage("Level2::Init");
	TraceMessage("---------------------");
	LoadResources("src/Assets/Jsons/Level2/Resources.json");
	LoadGameObjects("src/Assets/Jsons/Level2/GameObjects.json");

	// Add User Defined Components and objects// 
	GameObject* player = objectFactory->GetGameObjectByName("Player");
	player->AddComponent<PlayerControlComponent>();
	player->AddComponent<ScreenMoveComponent>();
	GameObject* firstEnemy = CreateEnemy();
	GameObject* fisrtStar = CreateStar();

	waveR = objectFactory->GetGameObjectByName("WaveR");
	waveL = objectFactory->GetGameObjectByName("WaveL");
	waveU = objectFactory->GetGameObjectByName("WaveU");
	waveD = objectFactory->GetGameObjectByName("WaveD");
	waveR->AddComponent<WaveComponent>();
	waveL->AddComponent<WaveComponent>();
	waveU->AddComponent<WaveComponent>();
	waveD->AddComponent<WaveComponent>();

	InitializeGameObjects();
	//CreateAllDebugCollisionAreas();


	BuildHiearchy("src/Assets/Jsons/Level2/Hierachy.json");
	AddGobjToRoot(firstEnemy);
	AddGobjToRoot(fisrtStar);
	waveR->SetAlive(false);
	waveL->SetAlive(false);
	waveU->SetAlive(false);
	waveD->SetAlive(false);



	// Regiseter UserDefined Events
	EventSystem* eventSystem = EventSystem::GetInstance();
	// member function pointer
	std::function<void(void*)> c(std::bind(&Level2::Level2CollisionCallback, this, std::placeholders::_1));
	collisionEventListener.SetCallback(c);
	collisionEventListener.SetType(EventType::Collision);
	std::function<void(void*)> w(std::bind(&Level2::Level2WaveCallback, this, std::placeholders::_1));
	waveEventListener.SetCallback(w);
	waveEventListener.SetType(EventType::Wave);
	eventSystem->AddListener(EventType::Collision, &collisionEventListener);
	eventSystem->AddListener(EventType::Wave, &waveEventListener);

	Score = 0;

	SetupCamara(gw);
	TraceMessage("---------------------");
	TraceMessage("Level2::Init finished");
	TraceMessage("---------------------");
}

void Level2::Update()
{
	Scene::Update();
}

void Level2::Destroy()
{
	// Remove UserDefined Events
	EventSystem* eventSystem = EventSystem::GetInstance();
	eventSystem->RemoveListener(EventType::Wave, &waveEventListener);
	eventSystem->RemoveListener(EventType::Collision, &collisionEventListener);

	Scene::Destroy();
}




void Level2::AddGobjToRoot(GameObject* gobj)
{
	root.AddChild(gobj);
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

	// Create Star
	GameObject* star = new GameObject();
	star->SetName("Star");
	star->SetMesh(newMesh);
	star->SetMaterial(resourceManager->GetMaterialByName("StarMaterial"));
	star->AddComponent<TransformComponent>();
	star->AddComponent<RenderComponent>();
	star->AddComponent<PhysicComponent>();
	star->AddComponent<StarComponent>();
	star->Init();
	return star;
}

// Event Callbacks for scene
void Level2::Level2CollisionCallback(void* eventData)
{
	CollisionEvent* converted = static_cast<CollisionEvent*>(eventData);
	if (converted)
	{

		// Player and Star collide, destroy star, add one point, 
		// generate new Star, generate new Enemy
		if (converted->gobj1->GetName() == "Player" && converted->gobj2->GetName() == "Star")
		{
			converted->gobj2->SetAlive(false);
			converted->gobj2->SetToBeDeleted();

			++Level2::Score;
			TraceMessage(("Score: " + std::to_string(Level2::Score)).c_str());
			this->AddGobjToRoot(this->CreateStar());
			this->AddGobjToRoot(this->CreateEnemy());

		}
		if (converted->gobj1->GetName() == "Star" && converted->gobj2->GetName() == "Player")
		{
			converted->gobj1->SetAlive(false);
			converted->gobj1->SetToBeDeleted();

			++Level2::Score;
			TraceMessage(("Score: " + std::to_string(Level2::Score)).c_str());
			this->AddGobjToRoot(this->CreateStar());
			this->AddGobjToRoot(this->CreateEnemy());
		}

		// Game Lost, go to result screen
		if (converted->gobj1->GetName() == "Player" && converted->gobj2->GetName() == "Enemy")
		{
			converted->gobj1->SetAlive(false);
			converted->gobj1->SetToBeDeleted();
			SceneChangeEvent sce("Level3");
			EventSystem::GetInstance()->BroadcastEvent(EventType::SceneChange, &sce);
		}
		if (converted->gobj1->GetName() == "Enemy" && converted->gobj2->GetName() == "Player")
		{
			converted->gobj2->SetAlive(false);
			converted->gobj2->SetToBeDeleted();
			SceneChangeEvent sce("Level3");
			EventSystem::GetInstance()->BroadcastEvent(EventType::SceneChange, &sce);
		}
	}

}
void Level2::Level2WaveCallback(void* eventData)
{
	WaveEvent* converted = static_cast<WaveEvent*>(eventData);
	if (converted)
	{

		// Draw wave (wave component controls setting alive false)
		if (converted->WaveSideName=="WaveR")
		{
			waveR->SetAlive(true);
		}
		if (converted->WaveSideName == "WaveL")
		{
			waveL->SetAlive(true);
		}
		if (converted->WaveSideName == "WaveU")
		{
			waveU->SetAlive(true);
		}
		if (converted->WaveSideName == "WaveD")
		{
			waveD->SetAlive(true);
		}

	}

}