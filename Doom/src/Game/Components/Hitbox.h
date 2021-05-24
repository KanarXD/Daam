#pragma once
#include "pch.h"
#include "Transform.h"

struct Hitbox
{ 
	static bool showHitbox;
	static std::string rdModelPath;
	static std::string sqModelPath;

	glm::vec3 offset;
	glm::vec3 scaleModifier;
	bool useRound;

	Hitbox(const glm::vec3& offset = glm::vec3(0), const glm::vec3& scaleModifier = glm::vec3(1), bool useRound = true);

	static bool CollisionDetection(const Transform& tA, const Hitbox& hA, const Transform& tB, const Hitbox& hB);
};

