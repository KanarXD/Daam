#include "pch.h"
#include "Combat.h"

Combat::Combat(float health, float attackDamege, float timeBetweenAttack)
	: health(health), maxHealth(health), attackDamege(attackDamege), timeBetweenAttack(timeBetweenAttack) {}

float Combat::DealDamage() const
{
	return attackDamege;
}

bool Combat::IsDead() const
{
	return health <= 0;
}
