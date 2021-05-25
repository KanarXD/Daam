#include "pch.h"
#include "Collisions.h"

bool Collisions::CylindersIntersect(const glm::vec3 & aPos, float aSize, const glm::vec3 & bPos, float bSize)
{
	float dist = glm::distance(aPos, bPos);
	return dist < aSize + bSize;
}

bool Collisions::CylinderBoxIntersect(const glm::vec3& rdPos, float rdSize, const glm::vec3& sqPos, const glm::vec3& sqSize)
{
	float cDistX = fabs(rdPos.x - sqPos.x);
	float cDistZ = fabs(rdPos.z - sqPos.z);

	if (cDistX > (sqSize.x + rdSize)) return false;
	if (cDistZ > (sqSize.z + rdSize)) return false;

	if (cDistX <= sqSize.x) return true;
	if (cDistZ <= sqSize.z) return true;

	float cornerSqDist = pow(cDistX - rdSize, 2) + pow(cDistZ - rdSize / 2, 2);

	return cornerSqDist <= (sqSize.x * sqSize.z);
}

bool Collisions::BoxesIntersect(const glm::vec3& aPos, const glm::vec3& aSize, const glm::vec3& bPos, const glm::vec3& bSize)
{
	bool isCollisionX = aPos.x + aSize.x > bPos.x - bSize.x && aPos.x - aSize.x < bPos.x + bSize.x;
	bool isCollisionZ = aPos.z + aSize.z > bPos.z - bSize.z && aPos.z - aSize.z < bPos.z + bSize.z;

	return isCollisionX && isCollisionZ;
}

bool Collisions::LinesIntersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	if (std::max(x1, x2) < std::min(x3, x4)) return false;

	float a1 = (y1 - y2) / (x1 - x2);
	float a2 = (y3 - y4) / (x3 - x4);

	if (a1 == a2) return false;

	float b1 = y1 - a1 * x1;
	float b2 = y3 - a2 * x3;

	float xA = (b2 - b1) / (a1 - a2);

	if (xA < std::max(std::min(x1, x2), std::min(x3, x4)) ||
		xA > std::min(std::max(x1, x2), std::max(x3, x4))) return false;

	return true;
}

bool Collisions::RayCastCylinder(const glm::vec3& from, const glm::vec3& to, const glm::vec3& rdPos, float rdSize)
{
	glm::vec3 n = glm::normalize(to - from);
	glm::vec2 t{ -n.y, n.x };
	glm::vec2 A = glm::vec2(rdPos.x, rdPos.z) + t * rdSize;
	glm::vec2 B = glm::vec2(rdPos.x, rdPos.z) - t * rdSize;

	return LinesIntersect(from.x, from.z, to.x, to.z, A.x, A.y, B.x, B.y);
}

bool Collisions::RayCastBox(const glm::vec3& from, const glm::vec3& to, const glm::vec3& sqPos, const glm::vec3& sqSize)
{
	bool t1 = LinesIntersect(from.x, from.z, to.x, to.z, sqPos.x - sqSize.x, sqPos.z - sqSize.z, sqPos.x + sqSize.x, sqPos.z + sqSize.z);
	bool t2 = LinesIntersect(from.x, from.z, to.x, to.z, sqPos.x - sqSize.x, sqPos.z + sqSize.z, sqPos.x + sqSize.x, sqPos.z - sqSize.z);
	if (t1 || t2) return true;
	return false;
}
