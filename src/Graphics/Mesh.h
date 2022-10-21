#pragma once
#include <glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float2.hpp>
#include <string>
#include <vector>
#include "Shader.h"
#include "Texture.h"
#include "Vertex.h"


class Mesh
{
public:

	std::vector<Vertex>       vertices;
	std::vector<unsigned int> indices;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    Mesh(Mesh& m);
    ~Mesh();

    void Draw();
    void SetDrawMode(GLenum glenum);


private:

    // render data 
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    //
    GLenum drawMode = GL_TRIANGLES;

    // initializes all the buffer objects/arrays
    void setupMesh();
};


