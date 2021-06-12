#pragma once
#include "Bullet.h"
class Enemy_Bullet : public Bullet
{
public:
	Enemy_Bullet(const Transform& transform, const std::string& type = "enemy_bullet");
};

