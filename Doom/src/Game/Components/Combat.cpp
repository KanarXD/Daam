#include "pch.h"
#include "Combat.h"

Combat::Combat(float health, float attackDamege, float attackTime)
	: health(health), attackDamege(attackDamege), attackTime(attackTime) {}

void Combat::TakeDamage(float damage)
{
	health -= damage;
}

float Combat::DealDamage() const
{
	return attackDamege;
}

bool Combat::IsDead() const
{
	return health <= 0;
}
