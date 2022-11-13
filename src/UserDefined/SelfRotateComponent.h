#pragma once
class SelfRotateComponent : public Component
{
public:
	SelfRotateComponent() {};
	~SelfRotateComponent() {};

	virtual void Init();
	virtual void Update();
	virtual void Destroy(); 
private:
	TransformComponent* tc;
};

