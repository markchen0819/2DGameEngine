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
	gameEngine = GameEngine::GetInstance();
	gameEngine->Initialize();

	TraceMessage("Create User Levels");
	Scene* scene1 = new Level1("Level1");
	Scene* scene2 = new Level2("Level2");
	Scenes.push_back(scene1);
	Scenes.push_back(scene2);


	gameEngine->SetAllScenes(Scenes);
	gameEngine->ChangeScene(scene1);
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
	Scenes.clear();
	gameEngine->Quit();
}

