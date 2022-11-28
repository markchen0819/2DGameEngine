#include "pch.h"

Level3::Level3(std::string name)
{
	TraceMessage(("Level3 ctor " + Name).c_str());
	Name = name;
}

Level3::~Level3()
{
	TraceMessage(("Level3 dtor " + Name).c_str());
}

void Level3::Init(GameWindow* gw)
{
	TraceMessage("---------------------");
	TraceMessage("Level3::Init");
	TraceMessage("---------------------");
	LoadResources("src/Assets/Jsons/Level3/Resources.json");
	LoadGameObjects("src/Assets/Jsons/Level3/GameObjects.json");

	// Add User Defined Components // 

	GameObject* picture = objectFactory->GetGameObjectByName("Result");
	picture->AddComponent<PressEnterToNextScreenComponent>();
	picture->GetComponent<PressEnterToNextScreenComponent>()->SetSceneName("Level1");
	
	DisplayScore();

	InitializeGameObjects();
	CreateAllDebugCollisionAreas();
	BuildHiearchy("src/Assets/Jsons/Level3/Hierachy.json");

	root.AddChild(digit1Gobj);
	root.AddChild(digit2Gobj);
	SetupCamara(gw);

	TraceMessage("---------------------");
	TraceMessage("Level3::Init finished");
	TraceMessage("---------------------");
}


void Level3::Update()
{
	Scene::Update();
}

void Level3::Destroy()
{
	//delete digit1Gobj; //already added to root
	//delete digit2Gobj;
	delete digit1Mat;
	delete digit2Mat;
	delete digit1Texture;
	delete digit2Texture;
	Scene::Destroy();
}

void Level3::DisplayScore()
{
	int score = Level2::Score;
	int digit1 = score % 10;
	int digit2 = score / 10;

	digit1Mat = new Material();
	digit2Mat = new Material();
	digit1Mat->AttachShader(resourceManager->GetShaderByName("SampleShader"));
	digit2Mat->AttachShader(resourceManager->GetShaderByName("SampleShader"));
	digit1Texture = CreateTextureByNumber(digit1);
	digit2Texture = CreateTextureByNumber(digit2);
	digit1Mat->AttachTexture(digit1Texture);
	digit2Mat->AttachTexture(digit2Texture);

	digit1Gobj = CreateDigitGameObject();
	digit1Gobj->SetMaterial(digit1Mat);
	TransformComponent* tc1 = digit1Gobj->GetComponent<TransformComponent>();
	tc1->SetRotation(180, 0, 0);
	tc1->SetScale(0.7, 0.7, 0.7);
	tc1->SetTranslation(30, 0, 0);

	digit2Gobj = CreateDigitGameObject();
	digit2Gobj->SetMaterial(digit2Mat);
	TransformComponent* tc2 = digit2Gobj->GetComponent<TransformComponent>();
	tc2->SetRotation(180, 0, 0);
	tc2->SetScale(0.7, 0.7, 0.7);
	tc2->SetTranslation(-30, 0, 0);


}
GameObject* Level3::CreateDigitGameObject()
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
	GameObject* newdigit = new GameObject();

	newdigit->SetName("Digit");
	newdigit->SetMesh(newMesh);

	newdigit->AddComponent<TransformComponent>();
	newdigit->AddComponent<RenderComponent>();
	newdigit->Init();

	return newdigit;
}

Texture* Level3::CreateTextureByNumber(int num)
{
	std::string textureStr = "src/Assets/Textures/" + std::to_string(num) + ".png";
	return new Texture(textureStr, "texture_diffuse");
}
