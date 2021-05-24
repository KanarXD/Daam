#pragma once
#include "Enemy.h"

class Enemy_Fast : public Enemy
{
private:
	static std::string fastModelPath;
	static Hitbox fastHitbox;
	static Specs fastSpecs;

public:
	Enemy_Fast(const Transform& transform, const std::string& type = "enemy_fast");

	void Update(float dt) override;
};

