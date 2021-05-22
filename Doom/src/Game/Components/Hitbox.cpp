#include "pch.h"
#include "Hitbox.h"
#include "Renderer/Renderer.h"
#include "Renderer/Library/ModelsLibrary.h"

bool Hitbox::showHitbox = false;
std::string Hitbox::rdModelPath = "res/models/Hitboxes/rdHitbox.obj";
std::string Hitbox::sqModelPath = "res/models/Hitboxes/sqHitbox.obj";

Hitbox::Hitbox(const glm::vec3& offset, const glm::vec3& scaleModifier, bool useRound)
	: offset(offset), scaleModifier(scaleModifier), useRound(useRound) {}

bool Hitbox::CollisionDetection(const Transform& tA, const Hitbox& hA, const Transform& tB, const Hitbox& hB)
{
	if (hA.useRound && hB.useRound) 
	{
		float dist = glm::distance(tA.position + hA.offset, tB.position + hB.offset);
		return dist < tA.scale.x * hA.scaleModifier.x + tB.scale.x * hB.scaleModifier.x;
	}
	else
	{
		glm::vec3 posA = tA.position + hA.offset;
		glm::vec3 sizeA = tA.scale * hA.scaleModifier;// / 2.0f;
		glm::vec3 posB = tB.position + hB.offset;
		glm::vec3 sizeB = tB.scale * hB.scaleModifier;// / 2.0f;

		if (!hA.useRound && !hB.useRound)
		{
			bool isCollisionX = posA.x + sizeA.x > posB.x - sizeB.x && posA.x - sizeA.x < posB.x + sizeB.x;
			bool isCollisionZ = posA.z + sizeA.z > posB.z - sizeB.z && posA.z - sizeA.z < posB.z + sizeB.z;

			return isCollisionX && isCollisionZ;
		}

		float cDistX = fabs(posA.x - posB.x);
		float cDistZ = fabs(posA.z - posB.z);

		if (cDistX > (sizeB.x + sizeA.x)) return false;
		if (cDistZ > (sizeB.z + sizeA.z)) return false;

		if (hA.useRound && !hB.useRound)
		{
			if (cDistX <= sizeB.x) return true;
			if (cDistZ <= sizeB.z) return true;

			float cornerSqDist = pow(cDistX - sizeB.x, 2) + pow(cDistZ - sizeB.z / 2, 2);

			return cornerSqDist <= (sizeA.x * sizeA.z);
		}
		else if (!hA.useRound && hB.useRound)
		{
			if (cDistX <= sizeA.x) return true;
			if (cDistZ <= sizeA.z) return true;

			float cornerSqDist = pow(cDistX - sizeA.x, 2) + pow(cDistZ - sizeA.z / 2, 2);

			return cornerSqDist <= (sizeB.x * sizeB.z);
		}
	}
}
