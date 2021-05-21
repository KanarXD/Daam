#include "pch.h"
#include "Hitbox.h"

bool Hitbox::showHitbox = false;
std::string Hitbox::modelPath = "";

Hitbox::Hitbox(const glm::vec3& offset, const glm::vec3& scaleModifier)
	: offset(offset), scaleModifier(scaleModifier) {}


glm::mat4 Hitbox::GetM(const Transform& objTransform) const
{
	return glm::scale(glm::translate(glm::mat4(1.0f), objTransform.position + offset), objTransform.scale * scaleModifier);
}
