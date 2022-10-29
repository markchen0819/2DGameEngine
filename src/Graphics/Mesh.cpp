#include "Mesh.h"


Mesh::Mesh()
{
    // will it double delete?
    SetDefaultSquareMesh();
}
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
    SetVerticesAndIndicies(vertices, indices);
    CreateMeshFromData();
}
Mesh::Mesh(Mesh& m) // Copy ctor
{
    DeleteMesh();
    SetVerticesAndIndicies(vertices, indices);
    CreateMeshFromData(); // when passed as a copy we need a new id
}
Mesh::~Mesh()
{
    vertices.clear();
    indices.clear();
    DeleteMesh();
}

void Mesh::Draw()
{
    // Draw mesh
    glBindVertexArray(VAO);
    glDrawElements(drawMode, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::SetDrawMode(GLenum glenum)
{
    drawMode = glenum;
}
void Mesh::SetVerticesAndIndicies(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
    this->vertices = vertices;
    this->indices = indices;
}
void Mesh::CreateMeshFromData()
{
    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);// 1. bind Vertex Array Object
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // 2. copy our vertices array in a vertex buffer for OpenGL to use
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);// 3. copy our index array in a element buffer for OpenGL to use
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}
void Mesh::DeleteMesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Mesh::SetDefaultSquareMesh()
{
    DeleteMesh();
    
    vertices.clear();
    indices.clear();

    Vertex v0(glm::vec3(100.0f, 100.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f));
    Vertex v1(glm::vec3(100.0f, -100.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f));
    Vertex v2(glm::vec3(-100.0f, -100.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f));
    Vertex v3(glm::vec3(-100.0f, 100.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f));
    vertices.push_back(v0);
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    indices = { 0, 1, 3, 
                1, 2 ,3 };

    CreateMeshFromData();
}
