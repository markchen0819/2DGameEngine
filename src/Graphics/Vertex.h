#pragma once

class Vertex
{
public:
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;

    Vertex(glm::vec3 p, glm::vec3 n, glm::vec2 t) : Position(p), Normal(n), TexCoords(t)
    { }
};