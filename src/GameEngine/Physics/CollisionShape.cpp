#include "pch.h"

CollisionShape::CollisionShape() { Type = ShapeType::NONE; }
CollisionShape::~CollisionShape() { }

void CollisionShape::SetScale(glm::vec3 s) { scale = s; }
glm::vec3 CollisionShape::GetScale() { return scale; }
