#include "CollisionManager.h"
#include "CollisionCircle.h"
#include "CollisionAABB.h"
#include "CollisionOBB.h"
#include <glm/gtx/string_cast.hpp>

CollisionManager::CollisionManager() { }
CollisionManager::~CollisionManager() { }

void CollisionManager::AddGameObjectForCollisionChecking(GameObject* gobj)
{
	gobjList.push_back(gobj);
}
void CollisionManager::CheckAllCollisions()
{
	std::vector<int> x;
	std::vector<int> y;

	for (int i = 0; i < gobjList.size(); i++)
	{
		for (int j = 0; j < gobjList.size(); j++) 
		{
			if (i!=j) 
			{
				// Prevent double check ( check(A,B), check(B,A))
				bool checked = false;
				for (int k = 0; k < x.size(); ++k)
				{

					if ((i == x[k] && j == y[k]) || (i == y[k] && j == x[k]))
					{
						checked = true;
						break;
					}
				}
				if (checked) { continue; }; // Checked before, skip this

				// CheckCollision
				if (CheckCollision((*gobjList[i]).body->collisionShape, (*gobjList[i]).body->Position, (*gobjList[j]).body->collisionShape, (*gobjList[j]).body->Position))
				{
					//std::cout << glfwGetTime() << "_Collide!" << std::endl;
					CollisionEvent c(*gobjList[i], *gobjList[j]);
					EventSystem::GetInstance()->BroadcastEvent(EventType::Collision, &c);
				}
				x.push_back(i);
				y.push_back(j);
			}
		}
	}

}

bool CheckCollisionCircleToCircle(CollisionShape* circle1, glm::vec3 center1, CollisionShape* circle2, glm::vec3 center2)
{
	float sqDistance = (center1.x - center2.x) * (center1.x - center2.x) + (center1.y - center2.y) * (center1.y - center2.y);
	float radius1 = ((CollisionCircle*)circle1)->Radius * circle1->GetScale().x;
	float radius2 = ((CollisionCircle*)circle2)->Radius * circle2->GetScale().x;
	float radiusSum = radius1 + radius2;

	if (sqDistance <= radiusSum * radiusSum)
	{
		return true;
	}

	return false;
}
bool CheckCollisionAABBToAABB(CollisionShape* aabbShape1, glm::vec3 center1, CollisionShape* aabbShape2, glm::vec3 center2)
{
	CollisionAABB* aabb1 = (CollisionAABB*)aabbShape1;
	CollisionAABB* aabb2 = (CollisionAABB*)aabbShape2;

	float scaleX = aabb1->GetScale().x;
	float scaleY = aabb1->GetScale().y;
	float r1 = center1.x + aabb1->Right * scaleX;
	float l1 = center1.x + aabb1->Left * scaleX;
	float u1 = center1.y + aabb1->Up * scaleY;
	float d1 = center1.y + aabb1->Down * scaleY;

	scaleX = aabb2->GetScale().x;
	scaleY = aabb2->GetScale().y;
	float r2 = center2.x + aabb2->Right * scaleX;
	float l2 = center2.x + aabb2->Left * scaleX;
	float u2 = center2.y + aabb2->Up * scaleY;
	float d2 = center2.y + aabb2->Down * scaleY;

	if (l1 > r2) return false;
	if (r1 < l2) return false;
	if (u1 < d2) return false;
	if (d1 > u2) return false;
	return true;
}
bool CheckCollisionOBBToOBB(CollisionShape* obbShape1, glm::vec3 center1, CollisionShape* obbShape2, glm::vec3 center2)
{
	CollisionOBB obb1Original = *(CollisionOBB*)obbShape1;
	CollisionOBB obb2Original = *(CollisionOBB*)obbShape2;
	CollisionOBB obb1 = *(CollisionOBB*)obbShape1;
	CollisionOBB obb2 = *(CollisionOBB*)obbShape2;
	CollisionOBB temp;

	// Apply rotation & scale
	for (int i = 0; i < (obb1).verticies.size(); ++i)
	{
		glm::mat4 t = glm::mat4{ 1,0,0,0,   0,1,0,0,   0,0,1,0,   (obb1).GetCenter().x, (obb1).GetCenter().y, (obb1).GetCenter().z, 1.0f };
		glm::mat4 r = (obb1).GetRotationMat();
		glm::mat4 s = glm::mat4{ (obb1).GetScale().x,0,0,0,   0,(obb1).GetScale().y,0,0,   0,0,(obb1).GetScale().z,0,   0,0,0,1 };
		glm::mat4 model = t * r * s * glm::mat4(1.0f);
		(obb1).verticies[i] = model * obb1Original.verticies[i];
	}
	for (int i = 0; i < (obb2).verticies.size(); ++i)
	{
		glm::mat4 t = glm::mat4{ 1,0,0,0,   0,1,0,0,   0,0,1,0,   (obb2).GetCenter().x, (obb2).GetCenter().y, (obb2).GetCenter().z, 1.0f };
		glm::mat4 r = (obb2).GetRotationMat();
		glm::mat4 s = glm::mat4{ (obb2).GetScale().x,0,0,0,   0,(obb2).GetScale().y,0,0,   0,0,(obb2).GetScale().z,0,   0,0,0,1 };
		glm::mat4 model = t * r * s * glm::mat4(1.0f);
		(obb2).verticies[i] = model * obb2Original.verticies[i];
	}

	// SAT (this code is acutally applicable to polygons)
	for (int shapeCount = 0; shapeCount < 2; shapeCount++)
	{
		if (shapeCount == 1) // Swap
		{
			temp = obb1;
			obb1 = obb2;
			obb2 = temp;
		}
		for (int v = 0; v < obb1.verticies.size(); ++v)
		{
			int nextV = (v + 1) % obb1.verticies.size();
			// get projectedAxis vector by vec2 subtraction
			glm::vec2 projectedAxis = glm::vec2( -(obb1.verticies[nextV].y - obb1.verticies[v].y) , obb1.verticies[nextV].x - obb1.verticies[v].x );
			// normalize
			float d = sqrtf(projectedAxis.x * projectedAxis.x + projectedAxis.y * projectedAxis.y); // expensive but need normalize..
			projectedAxis = { projectedAxis.x / d, projectedAxis.y / d };

			// project all points of obb1
			float min_obb1 = FLT_MAX, max_obb1 = -FLT_MAX;
			for (int p = 0; p < obb1.verticies.size(); ++p)
			{
				// point dot axis -> scale of projection 
				float q = (obb1.verticies[p].x * projectedAxis.x + obb1.verticies[p].y * projectedAxis.y);
				min_obb1 = std::min(min_obb1, q);
				max_obb1 = std::max(max_obb1, q);
			}

			// project all points of obb2
			float min_obb2 = FLT_MAX, max_obb2 = -FLT_MAX;
			for (int p = 0; p < obb2.verticies.size(); ++p)
			{
				// point dot axis -> length of projection
				float q = (obb2.verticies[p].x * projectedAxis.x + obb2.verticies[p].y * projectedAxis.y);
				min_obb2 = std::min(min_obb2, q);
				max_obb2 = std::max(max_obb2, q);
			}

			// overlap -> continue , don't overlap -> not colliding (similar to AABB)
			if (min_obb1 >= max_obb2 || min_obb2 >= max_obb1)
			{
				return false;
			}
		}
	}
	return true;
}
bool CollisionManager::CheckCollision(CollisionShape* shape1, glm::vec3 center1, CollisionShape* shape2, glm::vec3 center2)
{
	if (shape1->Type == ShapeType::CIRCLE && shape2->Type == ShapeType::CIRCLE)
	{
		return CheckCollisionCircleToCircle(shape1, center1, shape2, center2);
	}
	else if (shape1->Type == ShapeType::AABB && shape2->Type == ShapeType::AABB)
	{
		return CheckCollisionAABBToAABB(shape1, center1, shape2, center2);
	}
	else if (shape1->Type == ShapeType::OBB && shape2->Type == ShapeType::OBB)
	{
		return CheckCollisionOBBToOBB(shape1, center1, shape2, center2);
	}
	else
	{
		std::cout << "Collision between types not found" << std::endl;
		return false;
	}
}

