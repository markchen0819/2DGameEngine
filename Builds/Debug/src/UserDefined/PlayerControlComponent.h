#pragma once
class PlayerControlComponent : public Component
{
public:
	PlayerControlComponent() {};
	~PlayerControlComponent() {};

	virtual void Init();
	virtual void Update();
	virtual void Destroy();

private:
	TransformComponent* tc;
	PhysicComponent* pc;
};

