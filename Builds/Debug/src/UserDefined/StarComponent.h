#pragma once
class StarComponent : public Component
{
public:
	StarComponent() {};
	~StarComponent() {};

	virtual void Init();
	virtual void Update();
	virtual void Destroy();

private:
	TransformComponent* tc;
	PhysicComponent* pc;
	float boundaries = 275;
};

