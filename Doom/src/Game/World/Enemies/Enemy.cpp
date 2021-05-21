#include "pch.h"
#include "Enemy.h"
#include "Game/Player.h"
#include "EnemyManager.h"

Enemy::Specs Enemy::defualtSpecs{ Combat(), Hitbox(glm::vec3(0, 3, 0), glm::vec3(1, 3, 1)), "res/models/base/Base Mesh sculpt 2.obj", 60, 20, 10 };

Enemy::Specs::Specs(const Combat& combat, const Hitbox& hitbox, const std::string& modelPath, float fov, float viewDist, float speed)
	: combat(combat), hitbox(hitbox), modelPath(modelPath), fov(fov), viewDist(viewDist), speed(speed) {}


Enemy::Enemy(const Transform& transform)
	: rigidbody(), transform(transform), activeSpecs(Enemy::defualtSpecs), timer(0.0f) {}

void Enemy::Update(float dt)
{
	transform.Update(rigidbody, dt);
}

bool Enemy::PlayerInBound() const
{
	const Transform pt = Player::GetTransform();
	if (glm::distance(transform.position, pt.position) > activeSpecs.viewDist) return false;
	
	float xOffset = pt.position.x - transform.position.x;
	float zOffset = pt.position.z - transform.position.z;
	float angDeg = glm::degrees(atan2(xOffset, zOffset));
	if (fabs(angDeg) > activeSpecs.fov / 2.0f) return false;

	return true;
}

glm::mat4 Enemy::GetM() const
{
	return glm::scale(glm::translate(glm::mat4(1.0f), transform.position), transform.scale);
}


