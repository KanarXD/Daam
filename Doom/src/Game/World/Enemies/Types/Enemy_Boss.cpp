#include "pch.h"
#include "Enemy_Boss.h"

Enemy::Specs Enemy_Boss::bossSpecs{ Combat(2500, 200, 4), 200, 200, 5 };

Enemy_Boss::Enemy_Boss(const Transform& transform, const std::string& type)
	: Enemy(transform, type)
{
	activeSpecs = bossSpecs;
}

void Enemy_Boss::Update(float dt)
{
	Enemy::Update(dt);
}
