#pragma once

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


