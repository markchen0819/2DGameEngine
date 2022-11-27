#pragma once
class EnemyComponent : public Component
{
public:
	EnemyComponent() {};
	~EnemyComponent() {};

	virtual void Init();
	virtual void Update();
	virtual void Destroy(); 

private:
	TransformComponent* tc;
	PhysicComponent* pc;
	float speed = 150;
	float xdir = 1;
	float ydir = 1;
	float boundaries = 275;
};

