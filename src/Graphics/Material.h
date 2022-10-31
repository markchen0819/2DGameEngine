#pragma once

class Material
{
public:

	Material();
	~Material();

	void AttachShader(Shader* s);
	void AttachTexture(Texture* t);
	void SetColor(float r, float g, float b, float a);

	Shader* shader = nullptr;
	Texture* texture = nullptr;
	Color color;

private:


};

