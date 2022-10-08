#pragma once
#include <glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float2.hpp>
#include <string>
#include <vector>
#include "Shader.h"
#include "Texture.h"

class Vertex
{
public:
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;

    Vertex(glm::vec3 p, glm::vec3 n, glm::vec2 t): Position(p), Normal(n), TexCoords(t)
    { }
};

class Mesh
{
public:

	std::vector<Vertex>       vertices;
	std::vector<unsigned int> indices;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    Mesh(Mesh& m);
    ~Mesh();

    void Draw();

private:

    // render data 
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    // initializes all the buffer objects/arrays
    void setupMesh();
};


