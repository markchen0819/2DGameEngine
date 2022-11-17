#include "pch.h"

Scene::Scene()
{
	//TraceMessage("Scene ctor");
	resourceManager = ResourceManager::GetInstance();
	objectFactory = ObjectFactory::GetInstance();
	physicsManager = PhysicsManager::GetInstance();
}
Scene::Scene(std::string name) : Name(name)
{
	//TraceMessage(("Scene ctor "+ Name).c_str());
	resourceManager = ResourceManager::GetInstance();
	objectFactory = ObjectFactory::GetInstance();
	physicsManager = PhysicsManager::GetInstance();
}
Scene::~Scene()
{
	//TraceMessage(("Scene dtor " + Name).c_str());
}

void Scene::Init(GameWindow* gw)
{
	TraceMessage("---------------------");
	TraceMessage(" Scene::Init()");
	TraceMessage("---------------------");

	// Load scene data into memory here

	//LoadResources("src/Assets/Jsons/AllResources.json");
	//LoadGameObjects("src/Assets/Jsons/AllGameObjects.json");
	//BuildHiearchy("src/Assets/Jsons/Hierachy.json");
	//SetupCamara(gw);

	TraceMessage("---------------------");
	TraceMessage(" Scene::Init() finished");
	TraceMessage("---------------------");
}

void Scene::LoadResources(std::string filename) 
{
	TraceMessage("---------------------");
	TraceMessage("Scene::LoadResources");
	TraceMessage("---------------------");
	FILE* fp;
	rapidjson::Document doc;
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
	//
	std::string shadersStr = doc.FindMember(JSONConstants::SHADERS)->value.GetString();
	resourceManager->LoadAllShaders(shadersStr);
	TraceMessage("");
	std::string texturesStr = doc.FindMember(JSONConstants::TEXTURES)->value.GetString();
	resourceManager->LoadAllTextures(texturesStr);
	TraceMessage("");
	std::string materialsStr = doc.FindMember(JSONConstants::MATERIALS)->value.GetString();
	resourceManager->LoadAllMaterials(materialsStr);
	TraceMessage("");
	//
	fclose(fp);
}
void Scene::LoadGameObjects(std::string filename) 
{
	TraceMessage("---------------------");
	TraceMessage("Scene::LoadGameObjects");
	TraceMessage("---------------------");

	objectFactory->CreateAllGameObjects(filename);
}
void Scene::InitializeGameObjects()
{
	TraceMessage("---------------------");
	TraceMessage("Scene::InitGameObjects()");
	TraceMessage("---------------------");
	objectFactory->InitializeGameObjects();
}
void Scene::CreateAllDebugCollisionAreas()
{
	TraceMessage("---------------------");
	TraceMessage("Scene::CreateAllDebugCollisionAreas()");
	TraceMessage("---------------------");
	objectFactory->CreateAllDebugCollisionAreas();
}
void Scene::BuildHiearchy(std::string filename)
{
	TraceMessage("---------------------");
	TraceMessage("Scene::BuildHiearchy");
	TraceMessage("---------------------");
	FILE* fp;
	rapidjson::Document doc;
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
	//
	const rapidjson::Value& nodes = doc.FindMember(JSONConstants::ROOT)->value;
	for (rapidjson::Value::ConstMemberIterator itr = nodes.MemberBegin(); itr != nodes.MemberEnd(); ++itr)
	{
		recursiveBuildHierachy(itr, &root);
	}
	//
	fclose(fp);

	objectFactory->CheckAllGameObjectsInHierachy();
}
void Scene::recursiveBuildHierachy(rapidjson::Value::ConstMemberIterator nodeIterator, Node* parent)
{
	std::string nodeName = nodeIterator->name.GetString();
	GameObject* childNode = objectFactory->GetGameObjectByName(nodeName);
	parent->AddChild(childNode);
	objectFactory->SetGameObjectInHierachy(nodeName);
	TraceMessage((nodeName + " added to hierachy").c_str());
	const rapidjson::Value& childsOfChildNode = nodeIterator->value;
	if (childsOfChildNode.IsObject())
	{
		for (rapidjson::Value::ConstMemberIterator it = childsOfChildNode.MemberBegin(); it != childsOfChildNode.MemberEnd(); ++it)
		{
			recursiveBuildHierachy(it, childNode);
		}
	}
}
void Scene::SetupCamara(GameWindow* window)
{
	TraceMessage("---------------------");
	TraceMessage("Scene::SetupCamara");
	TraceMessage("---------------------");

	Renderer* renderer = Renderer::GetInstance();
	Shader* cameraShader = resourceManager->GetShaderByName("CameraShader");
	Shader* sampleShader = resourceManager->GetShaderByName("SampleShader");
	(*cameraShader).useProgram();
	Camera camera(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), window->Props.Heigth, window->Props.Width);
	camera.SetShaderVP(*cameraShader);
	(*renderer).UnuseShaderProgram();
	(*sampleShader).useProgram();
	camera.SetShaderVP(*sampleShader);
	(*renderer).UnuseShaderProgram();
}
void Scene::DeferredDeleteGameObject()
{
	// Remove from the scene hierachy (nullptr fixes)
	const std::vector<GameObject*> gameObjectsToDelete = objectFactory->GetGameObjectsToDeleteVector();
	for (GameObject* gobj : gameObjectsToDelete)
	{
		TraceMessage("---------------------");
		TraceMessage("Scene::DeferredDeleteGameObject()");
		TraceMessage("---------------------");
		(*gobj).GetParent()->RemoveChild(gobj);
	}
	// Actual Object Deletion (free memory of objects)
	objectFactory->DeferredDeleteGameObjects();
}

void Scene::Update()
{
	if (!isRunning) return;
	root.Update();
}
void Scene::LateUpdate()
{
	if (!isRunning) return;
	(*physicsManager).collisionManager.CheckAllCollisions();
	(*physicsManager).Integrate();
	DeferredDeleteGameObject();
}
void Scene::Draw()
{
	if (!isRunning) return;
	root.Draw();
}
void Scene::Destroy()
{
	TraceMessage("---------------------");
	TraceMessage((" Scene::Destroy() " + Name).c_str());
	TraceMessage("---------------------");
	root.Destroy();
	resourceManager->UnloadAllResources();
}

void Scene::Pause()
{
	TraceMessage("---------------------");
	TraceMessage((" Scene::Pause() "+Name).c_str());
	TraceMessage("---------------------");
	isRunning = false;
}

void Scene::Resume()
{
	TraceMessage("---------------------");
	TraceMessage((" Scene::Resume() " + Name).c_str());
	TraceMessage("---------------------");
	isRunning = true;
}
