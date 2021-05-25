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
		return Collisions::CylindersIntersect(tA.position + hA.offset, tA.scale.x * hA.scaleModifier.x,
			tB.position + hB.offset, tB.scale.x * hB.scaleModifier.x);
	else
	{
		glm::vec3 aPos = tA.position + hA.offset;
		glm::vec3 aSize = tA.scale * hA.scaleModifier;
		glm::vec3 bPos = tB.position + hB.offset;
		glm::vec3 bSize = tB.scale * hB.scaleModifier;

		if (!hA.useRound && !hB.useRound) 
			return Collisions::BoxesIntersect(aPos, aSize, bPos, bSize);
		else if (hA.useRound && !hB.useRound) 
			return Collisions::CylinderBoxIntersect(aPos, aSize.x, bPos, bSize);
		else  
			return Collisions::CylinderBoxIntersect(bPos, bSize.x, aPos, aSize);
	}
}
