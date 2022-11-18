#pragma once

class GameEngine
{

public:
	~GameEngine();
	static GameEngine* GetInstance();

	void Initialize();
	void Quit();

	void SetAllScenes(std::vector<Scene*>& scenes);
	void DeleteAllScenes();
	void ChangeScene(Scene* scene);
	void PushScene(Scene* scene);
	void PopScene();

	// Change scene at the end of frame for safety
	Scene* GetSceneByName(std::string sceneName);
	void AddSceneToChange(std::string sceneName);
	void DeferredChangeScene();

	void Update();
	void Draw();
	void PostUpdate();

	bool IsRunning();
	GameWindow* GetMainWindow();

private:
	GameEngine() {};

	static GameEngine* instance;
	ServiceLocator* serviceLocator;
	GameWindow* mainWindow;

	std::vector<Scene*> AllScenes; // All scenes created by the game
	std::stack<Scene*> scenesStack; // Current state of scenes of the game
	bool isRunning = false;

	EventListener collisionEventLister;
	EventListener sceneChangeEventLister;

	std::vector<std::string> sceneToChange;

};

