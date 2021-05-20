#include "pch.h"
#include "Enemy.h"
#include "Game/Player.h"
#include "EnemyManager.h"

Enemy::Enemy(Type type, const EnemySpecs* specs, const Transform& transform, float health)
	: type(type), specs(specs), rigidbody(), transform(transform), health(health) {}

bool Enemy::PlayerInBound() const
{
	const Transform pt = Player::GetTransform();
	if (glm::distance(transform.position, pt.position) > specs->viewDist) return false;
	
	float xOffset = pt.position.x - transform.position.x;
	float zOffset = pt.position.z - transform.position.z;
	float angDeg = glm::degrees(atan2(xOffset, zOffset));
	if (fabs(angDeg) > specs->fov / 2.0f) return false;

	return true;
}

const glm::mat4& Enemy::GetM() const
{
	return glm::scale(glm::translate(glm::mat4(1.0f), transform.position), transform.scale);
}


