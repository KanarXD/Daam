#pragma once
#include "Enemy.h"

class Enemy_Boss : public Enemy
{
private:
	static std::string bossModelPath;
	static Hitbox bossHitbox;
	static Specs bossSpecs;

public:
	Enemy_Boss(const Transform& transform, const std::string& type = "enemy_boss");

	void Update(float dt) override;
};

