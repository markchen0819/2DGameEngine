#pragma once
class WaveComponent: public Component
{
public:
	WaveComponent() {};
	~WaveComponent() {};

	virtual void Init();
	virtual void Update();
	virtual void Destroy();

	void ResetTimer();

private:
	float timeLimit = 0.17;
	float timer = 0;
};

