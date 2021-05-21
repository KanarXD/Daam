#pragma once
#include "pch.h"
#include "Transform.h"

class Hitbox
{
private:
	static bool showHitbox;
	static std::string modelPath;

	glm::vec3 offset;
	glm::vec3 scaleModifier;

public:
	Hitbox(const glm::vec3& offset, const glm::vec3& scaleModifier);
	glm::mat4 GetM(const Transform& objTransform) const;

	static bool IsShowHitbox() { return showHitbox; }
	static void SetShowHitbox(bool showHitbox) { Hitbox::showHitbox = showHitbox; }
	static void InitModelPath(const std::string& modelPath) { Hitbox::modelPath = modelPath; }
	static const std::string& GetModelPath() { return modelPath; };
};

