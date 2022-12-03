#pragma once
class Root : public Node
{
	// Only used as the center and the top hierachy of the scene

public:
	Root() { Name = "Root"; };
	~Root() {};

	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

};

