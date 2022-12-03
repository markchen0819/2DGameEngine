#include "pch.h"

CollisionAreaObject::CollisionAreaObject() 
{ 
	SetDefaultShape();
}
CollisionAreaObject::~CollisionAreaObject(){ }

void CollisionAreaObject::Init()
{

}

void CollisionAreaObject::Update()
{
	GameObject* parent = static_cast<GameObject*>(GetParent());
	UpdateTransform(*((*parent).transform));
}

void CollisionAreaObject::Destroy()
{
}
void CollisionAreaObject::Draw()
{
	Renderer::GetInstance()->Draw(Name, transform, mesh, material);
}


// Create a default 10x10 OBB shape
void CollisionAreaObject::SetDefaultShape() 
{
	delete transform;
	//Create Transform
	transform = new Transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

	//Create Mesh
	std::vector<glm::vec4> coord;
	coord.push_back(glm::vec4(100.0f, 100.0f, 0.0f, 1.0f));
	coord.push_back(glm::vec4(100.0f, -100.0f, 0.0f, 1.0f));
	coord.push_back(glm::vec4(-100.0f, -100.0f, 0.0f, 1.0f));
	coord.push_back(glm::vec4(-100.0f, 100.0f, 0.0f, 1.0f));
	// OBB
	SetMesh(coord);
}
// Circle
void CollisionAreaObject::SetMesh(float radius)
{
	shapeType = ShapeType::CIRCLE;
	delete mesh;
	//Create Mesh
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices =
	{0,1,2,
	 1,2,3,
	 2,3,4,
	 3,4,5,
	 4,5,6,
	 5,6,7,
	 6,7,0,
	 7,0,1};
	float r = radius;
	float rDividesqrt2 = r / 1.414;

	Vertex v0(glm::vec3(r, 0, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)); //R
	Vertex v1(glm::vec3(rDividesqrt2, -rDividesqrt2, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f));//RD
	Vertex v2(glm::vec3(0, -r, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)); //D
	Vertex v3(glm::vec3(-rDividesqrt2, -rDividesqrt2, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f));//LD
	Vertex v4(glm::vec3(-r,0, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f));//L
	Vertex v5(glm::vec3(-rDividesqrt2, rDividesqrt2, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f));//LU
	Vertex v6(glm::vec3(0, r, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f));//U
	Vertex v7(glm::vec3(rDividesqrt2, rDividesqrt2, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f));//RU


	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);
	vertices.push_back(v5);
	vertices.push_back(v6);
	vertices.push_back(v7);
	mesh = new Mesh(vertices, indices);
	mesh->SetDrawMode(GL_LINE_LOOP);
}
// AABB
void CollisionAreaObject::SetMesh(float r, float l, float u, float d)
{
	shapeType = ShapeType::AABB;
	delete mesh;
	//Create Mesh
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices =
	{ 0, 1, 3,
	1, 2, 3 };
	Vertex v0(glm::vec3(r, u, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
	Vertex v1(glm::vec3(r, d, 0.0), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f));
	Vertex v2(glm::vec3(l, d, 0.0), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f));
	Vertex v3(glm::vec3(l, u, 0.0), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f));
	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	mesh = new Mesh(vertices, indices);
	mesh->SetDrawMode(GL_LINE_LOOP);
}
// OBB
void CollisionAreaObject::SetMesh(std::vector<glm::vec4> v)
{
	shapeType = ShapeType::OBB;
	delete mesh;
	//Create Mesh
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices =
	{ 0, 1, 3,
	1, 2, 3 };
	Vertex v0(v[0], glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f));
	Vertex v1(v[1], glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f));
	Vertex v2(v[2], glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f));
	Vertex v3(v[3], glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f));
	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	mesh = new Mesh(vertices, indices);
	mesh->SetDrawMode(GL_LINE_LOOP);
}


void CollisionAreaObject::UpdateTransform(const Transform t)
{
	*transform = t;

	if (shapeType == ShapeType::AABB || shapeType == ShapeType::CIRCLE)
	{
		transform->SetRotation(0, 0, 0);
	}
}

void CollisionAreaObject::SetMaterial(Material* m)
{
	material = m;
}


