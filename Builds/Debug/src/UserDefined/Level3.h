#pragma once
class Level3 : public Scene
{
public:

	Level3(std::string name);
	~Level3();
	virtual void Init(GameWindow* gw);
	virtual void Update();
	virtual void Destroy();

private:
	GameObject* digit1Gobj;
	GameObject* digit2Gobj;
	Material* digit1Mat;
	Material* digit2Mat;
	Texture* digit1Texture;
	Texture* digit2Texture;

	void DisplayScore();
	GameObject* CreateDigitGameObject();
	Texture* CreateTextureByNumber(int num);
};
