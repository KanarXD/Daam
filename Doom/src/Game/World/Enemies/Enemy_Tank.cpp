#include "pch.h"
#include "Enemy_Tank.h"

Enemy::Specs Enemy_Tank::tankSpecs{ Combat(500, 10, 1000), 100, 20, 10 };

Enemy_Tank::Enemy_Tank(const Transform& transform, const std::string& type)
	: Enemy(transform, type)
{
	activeSpecs = tankSpecs;
}

void Enemy_Tank::Update(float dt)
{
	Enemy::Update(dt);
	transform.position.y += sin(timer * 2) / 30;
}
