#pragma once
#include "Enemy.h"

class Enemy_Tank : public Enemy
{
private:
	static std::string tankModelPath;
	static Hitbox tankHitbox;
	static Specs tankSpecs;

public:
	Enemy_Tank(const Transform& transform, const std::string& type = "enemy_tank");

	void Update(float dt) override;
};

