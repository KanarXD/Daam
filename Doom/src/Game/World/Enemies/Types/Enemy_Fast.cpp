#include "pch.h"
#include "Enemy_Fast.h"

Enemy::Specs Enemy_Fast::fastSpecs{ Combat(150, 30, 0.5f), 160, 100, 15 };

Enemy_Fast::Enemy_Fast(const Transform& transform, const std::string& type)
	: Enemy(transform, type)
{
	activeSpecs = fastSpecs;
}

void Enemy_Fast::Update(float dt)
{
	Enemy::Update(dt);
}
