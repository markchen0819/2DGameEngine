#include "pch.h"

Game* Game::instance = nullptr;
Game* Game::GetInstance()
{
	static Game* instance = new Game();
	return instance;
}
Game::~Game()
{
	delete instance;
}

void Game::Init()
{
	TraceInit();
	gameEngine = GameEngine::GetInstance();
	gameEngine->Initialize();


	TraceMessage("---------------------");
	TraceMessage("Create Game Levels");
	TraceMessage("---------------------");
	Scene* scene2 = new Level2("Level2");
	Scenes.push_back(scene2);


	gameEngine->SetAllScenes(Scenes);
	gameEngine->ChangeScene(scene2);
}
void Game::Run()
{
	while (gameEngine->IsRunning())
	{
		gameEngine->Update();
		gameEngine->Draw();
		gameEngine->PostUpdate();
	}
}
void Game::Reset()
{

}
void Game::Quit()
{
	gameEngine->Quit();

	TraceMessage("---------------------");
	TraceMessage("Destroy Game Levels");
	TraceMessage("---------------------");
	for (Scene* s : Scenes)
	{
		delete s;
	}

	TraceShutdown();
}

