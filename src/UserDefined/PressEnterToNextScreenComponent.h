#pragma once
class PressEnterToNextScreenComponent : public Component
{
public:
	PressEnterToNextScreenComponent() {};
	~PressEnterToNextScreenComponent() {};

	virtual void Init();
	virtual void Update();
	virtual void Destroy();


	void SetSceneName(std::string name);
private:
	std::string sceneName;
};

