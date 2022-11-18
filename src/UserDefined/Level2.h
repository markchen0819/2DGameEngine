#pragma once
class Level2 : public Scene
{
public:

	Level2(std::string name);
	~Level2();
	virtual void Init(GameWindow* gw);
	virtual void Update();
private:
	EventListener e;
};

