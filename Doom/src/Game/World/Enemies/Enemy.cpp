#include "pch.h"
#include "Enemy.h"
#include "Game/Player.h"

Enemy::Specs Enemy::defualtSpecs{ Combat(), 60, 20, 10 };

Enemy::Specs::Specs(const Combat& combat, float fov, float viewDist, float speed)
	: combat(combat), fov(fov), viewDist(viewDist), speed(speed) {}


Enemy::Enemy(const Transform& transform, const std::string& type)
	: GameObject(transform, type),  rigidbody(), activeSpecs(Enemy::defualtSpecs) {}

void Enemy::Update(float dt)
{
	GameObject::Update(dt);
	transform.Update(rigidbody, dt);
}

void Enemy::Collision(const GameObject& collidedObject)
{
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
