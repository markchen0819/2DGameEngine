#include "pch.h"

Material::Material()
{
}

Material::~Material()
{
}

void Material::AttachShader(Shader* s)
{
	shader = s;
}

void Material::AttachTexture(Texture* t)
{
	texture = t;
}

void Material::SetColor(float r, float g, float b, float a)
{
	color.SetColor(r, g, b, a);
}

void Material::SetName(std::string name)
{
	Name = name;
}

std::string Material::GetName()
{
	return Name;
}
