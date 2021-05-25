#include "pch.h"
#include "Combat.h"

Combat::Combat(float health, float attackDamege, float attackTime)
	: health(health), maxHealth(health), attackDamege(attackDamege), attackTime(attackTime) {}

float Combat::DealDamage() const
{
	return attackDamege;
}

bool Combat::IsDead() const
{
	return health <= 0;
}
