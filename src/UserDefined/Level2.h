#pragma once
class Level2 : public Scene
{
public:

	Level2(std::string name);
	~Level2();
	virtual void Init(GameWindow* gw);
	virtual void Update();
	virtual void Destroy();

	static int Score;
	GameObject* CreateEnemy();
	GameObject* CreateStar();
	void AddGobjToRoot(GameObject* gobj);


	// Referenece
	GameObject* waveU;
	GameObject* waveR;
	GameObject* waveL;
	GameObject* waveD;

private:
	EventListener collisionEventListener;
	EventListener waveEventListener;
	void Level2CollisionCallback(void* eventData);
	void Level2WaveCallback(void* eventData);

};

