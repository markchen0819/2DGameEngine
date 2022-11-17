#pragma once

class Color
{
public:
	Color();
	Color(float r, float g, float b, float a);
	~Color();

	void SetColor(float r, float g, float b, float a);
	glm::vec4 color;
private:

};
