#include "pch.h"

Color::Color()
{
	color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

Color::Color(float r, float g, float b, float a) 
{ 
	color = glm::vec4(r, g, b, a); 
}

Color::~Color()
{

}
void Color::SetColor(float r, float g, float b, float a)
{
	color = glm::vec4(r, g, b, a);
}