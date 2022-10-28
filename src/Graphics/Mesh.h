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

    Mesh();
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    Mesh(Mesh& m);
    ~Mesh();

    void Draw();

    // initializes all the buffer objects/arrays
    void SetDrawMode(GLenum glenum);
    void SetVerticesAndIndicies(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    void CreateMeshFromData();
    void DeleteMesh();

    //default shapes for convenient
    void SetDefaultSquareMesh();

private:

    GLenum drawMode = GL_TRIANGLES;
    // render data 
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

};


