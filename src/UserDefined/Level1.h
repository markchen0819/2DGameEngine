#pragma once
class Level1 : public Scene
{
public:

	Level1(std::string name);
	~Level1();
	virtual void Init(GameWindow* gw);
	virtual void Update();
};
