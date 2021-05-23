#include "pch.h"
#include "Enemy.h"
#include "Game/Player.h"
#include "Game/GameObjectManager.h"

Enemy::Specs Enemy::defualtSpecs{ Combat(), 80, 30, 10 };

Enemy::Specs::Specs(const Combat& combat, float fov, float viewDist, float speed)
	: combat(combat), fov(fov), viewDist(viewDist), speed(speed) {}


Enemy::Enemy(const Transform& transform, const std::string& type)
	: GameObject(transform, type),  rigidbody(), activeSpecs(Enemy::defualtSpecs) 
{
	this->transform.rotation.y = float(rand() % 100) / 24;
}

void Enemy::Update(float dt)
{
	GameObject::Update(dt);
	if (PlayerInBound())
	{
		glm::vec3 playerPos = Player::GetTransform().position;
		transform.rotation.y = atan2(playerPos.x - transform.position.x, playerPos.z - transform.position.z);
		rigidbody.velocity.z = activeSpecs.speed;
	}
	else
		rigidbody.velocity.z = 0;
	transform.Update(rigidbody, dt);
}

void Enemy::Collision(const GameObject& collidedObject)
{
}

bool Enemy::PlayerInBound() const
{
	const Transform pt = Player::GetTransform();
	float dist = glm::distance(transform.position, pt.position);
	if (dist > activeSpecs.viewDist) return false;
	
	float xOffset = pt.position.x - transform.position.x;
	float zOffset = pt.position.z - transform.position.z;

	float ang = atan2(xOffset, zOffset);

	float angDiff = fabs(glm::degrees(ang - transform.rotation.y));
	if (angDiff > 180) angDiff -= 360;
	if (fabs(angDiff) > activeSpecs.fov / 2.0f) return false;

	return !GameObjectManager::GetInstance()->Ray(transform.position, Player::GetInstance()->GetTransform().position, "box");
	
	return true;
}
