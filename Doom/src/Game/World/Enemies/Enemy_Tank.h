#pragma once
#include "Enemy.h"

class Enemy_Tank : public Enemy
{
private:
	static Specs tankSpecs;

public:
	Enemy_Tank(const Transform& transform);

	void Update(float dt) override;
};

