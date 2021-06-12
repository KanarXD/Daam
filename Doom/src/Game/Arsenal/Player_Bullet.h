#pragma once
#include "Bullet.h"
class Player_Bullet : public Bullet
{
public:
	Player_Bullet(const Transform& transform, const std::string& type = "player_bullet");
};

