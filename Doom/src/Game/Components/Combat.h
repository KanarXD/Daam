#pragma once

struct Combat
{
	float health;
	float maxHealth;
	float attackDamege;
	float lastAttackTime{ 0 };
	float timeBetweenAttack;

	Combat(float health = 100.0f, float attackDamege = 10.0f, float timeBetweenAttack = 2.0f);

	float DealDamage() const;
	bool IsDead() const;
};