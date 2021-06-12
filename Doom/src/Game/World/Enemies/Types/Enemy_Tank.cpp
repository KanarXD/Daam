#include "pch.h"
#include "Enemy_Tank.h"
#include "Game/GameObjectManager.h"
#include "Game/Arsenal/Bullets.h"

Enemy::Specs Enemy_Tank::tankSpecs{ Combat(1000, 100, 3), 180, 120, 10 };

Enemy_Tank::Enemy_Tank(const Transform& transform, const std::string& type)
	: Enemy(transform, type)
{
	activeSpecs = tankSpecs;
}

void Enemy_Tank::Update(float dt)
{
	Enemy::Update(dt);
	if (playerInBound)
		Shoot();
}

void Enemy_Tank::Shoot()
{
	if (timer - activeSpecs.combat.lastAttackTime > activeSpecs.combat.timeBetweenAttack / 10.0f)
	{
		activeSpecs.combat.lastAttackTime = timer;
		GameObjectManager::GetInstance()->Add<Enemy_Bullet>(
			Transform(transform.position + glm::vec3(0, -1, 0), transform.rotation, glm::vec3(5)));
	}
}
