#pragma once

namespace Collisions
{
	bool CylindersIntersect(const glm::vec3& aPos, float aSize, const glm::vec3& bPos, float bSize);
	bool CylinderBoxIntersect(const glm::vec3& rdPos, float rdSize, const glm::vec3& sqPos, const glm::vec3& sqSize);
	bool BoxesIntersect(const glm::vec3& aPos, const glm::vec3& aSize, const glm::vec3& bPos, const glm::vec3& bSize);
	bool LinesIntersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);


	bool RayCastCylinder(const glm::vec3& from, const glm::vec3& to, const glm::vec3& rdPos, float rdSize);
	bool RayCastBox(const glm::vec3& from, const glm::vec3& to, const glm::vec3& sqPos, const glm::vec3& sqSize);
}
