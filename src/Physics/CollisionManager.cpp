#include "CollisionManager.h"
#include "CollisionCircle.h"
#include "CollisionAABB.h"
#include "CollisionOBB.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

bool CheckCollisionCircleToCircle(CollisionShape* circle1, float center1_x, float center1_y, CollisionShape* circle2, float center2_x, float center2_y)
{
	float sqDistance = (center1_x - center2_x) * (center1_x - center2_x) + (center1_y - center2_y) * (center1_y - center2_y);
	float radius1 = ((CollisionCircle*)circle1)->Radius;
	float radius2 = ((CollisionCircle*)circle2)->Radius;
	float radiusSum = radius1 + radius2;

	if (sqDistance <= radiusSum * radiusSum)
	{
		return true;
	}

	return false;
}
bool CheckCollisionAABBToAABB(CollisionShape* aabbShape1, float center1_x, float center1_y, CollisionShape* aabbShape2, float center2_x, float center2_y)
{
	CollisionAABB* aabb1 = (CollisionAABB*)aabbShape1;
	CollisionAABB* aabb2 = (CollisionAABB*)aabbShape2;

	float r1 = center1_x + aabb1->Right;
	float l1 = center1_x + aabb1->Left;
	float u1 = center1_y + aabb1->Up;
	float d1 = center1_y + aabb1->Down;

	float r2 = center2_x + aabb2->Right;
	float l2 = center2_x + aabb2->Left;
	float u2 = center2_y + aabb2->Up;
	float d2 = center2_y + aabb2->Down;

	if (l1 > r2) return false;
	if (r1 < l2) return false;
	if (u1 < d2) return false;
	if (d1 > u2) return false;
	return true;
}
bool CheckCollisionOBBToOBB(CollisionShape* obbShape1, float center1_x, float center1_y, CollisionShape* obbShape2, float center2_x, float center2_y)
{
	CollisionOBB* obb1 = (CollisionOBB*)obbShape1;
	CollisionOBB* obb2 = (CollisionOBB*)obbShape2;

	// SAT (this code is acutally applicable to polygons)
	for (int shapeCount = 0; shapeCount < 2; shapeCount++)
	{
		if (shapeCount == 1) // Swap
		{
			obb1 = (CollisionOBB*)obbShape2;
			obb2 = (CollisionOBB*)obbShape1;
		}

		for (int v = 0; v < obb1->verticies.size(); ++v)
		{
			int nextV = (v + 1) % obb1->verticies.size();
			// get projectedAxis vector by vec2 subtraction
			glm::vec2 projectedAxis =
			{ -(obb1->verticies[nextV].y - obb1->verticies[v].y) , obb1->verticies[nextV].x - obb1->verticies[v].x };
			// normalize
			float d = sqrtf(projectedAxis.x * projectedAxis.x + projectedAxis.y * projectedAxis.y);
			projectedAxis = { projectedAxis.x / d, projectedAxis.y / d };

			// project all points of obb1
			float min_obb1 = FLT_MAX, max_obb1 = -FLT_MAX;
			for (int p = 0; p < obb1->verticies.size(); ++p)
			{
				// point dot axis -> scale of projection 
				float q = (obb1->verticies[p].x * projectedAxis.x + obb1->verticies[p].y * projectedAxis.y);
				min_obb1 = std::min(min_obb1, q);
				max_obb1 = std::max(max_obb1, q);
			}

			// project all points of obb2
			float min_obb2 = FLT_MAX, max_obb2 = -FLT_MAX;
			for (int p = 0; p < obb1->verticies.size(); ++p)
			{
				// point dot axis -> length of projection
				float q = (obb2->verticies[p].x * projectedAxis.x + obb2->verticies[p].y * projectedAxis.y);
				min_obb1 = std::min(min_obb2, q);
				max_obb1 = std::max(max_obb2, q);
			}

			// overlap -> continue , don't overlap -> not colliding (similar to AABB)
			if (!(max_obb2 >= min_obb1 && max_obb1 >= min_obb2))
				return false;
		}
	}
	return true;
}
bool CollisionManager::CheckCollision(CollisionShape* shape1, float pos1_x, float pos1_y, CollisionShape* shape2, float pos2_x, float pos2_y)
{
	if (shape1->Type == ShapeType::CIRCLE && shape2->Type == ShapeType::CIRCLE)
	{
		return CheckCollisionCircleToCircle(shape1, pos1_x, pos1_y, shape2, pos2_x, pos2_y);
	}
	else if (shape1->Type == ShapeType::AABB && shape2->Type == ShapeType::AABB)
	{
		return CheckCollisionAABBToAABB(shape1, pos1_x, pos1_y, shape2, pos2_x, pos2_y);
	}
	else if (shape1->Type == ShapeType::OBB && shape2->Type == ShapeType::OBB)
	{
		return CheckCollisionOBBToOBB(shape1, pos1_x, pos1_y, shape2, pos2_x, pos2_y);
	}
	else
	{
		return CheckCollisionAABBToAABB(shape1, pos1_x, pos1_y, shape2, pos2_x, pos2_y);
	}

}

