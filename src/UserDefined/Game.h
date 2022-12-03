#pragma once
class Game
{

public:
	~Game();
	static Game* GetInstance();

	void Init();
	void Run();
	void Reset();
	void Quit();

private:
	Game() {};
	static Game* instance;
	GameEngine* gameEngine;

	std::vector<Scene*> Scenes; // Levels created by the user
};

