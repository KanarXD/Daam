#include "pch.h"
#include "Enemy_Fast.h"

Enemy::Specs Enemy_Fast::fastSpecs{ Combat(500, 10, 1000), 160, 30, 50 };

Enemy_Fast::Enemy_Fast(const Transform& transform, const std::string& type)
	: Enemy(transform, type)
{
	activeSpecs = fastSpecs;
}

void Enemy_Fast::Update(float dt)
{
	Enemy::Update(dt);
}
