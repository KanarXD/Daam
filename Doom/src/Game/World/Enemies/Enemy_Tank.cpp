#include "pch.h"
#include "Enemy_Tank.h"

Enemy::Specs Enemy_Tank::tankSpecs{ Combat(500, 10, 1000), "res/models/Enemy1/enemy1.obj", 100, 20, 10 };

Enemy_Tank::Enemy_Tank(const Transform& transform)
	: Enemy(transform)
{
	activeSpecs = tankSpecs;
}

void Enemy_Tank::Update(float dt)
{
	timer += dt;
	transform.position.y += sin(timer * 2000) / 20;
}
