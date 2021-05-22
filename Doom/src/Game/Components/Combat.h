#pragma once

struct Combat
{
	float health;
	float maxHealth;
	float attackDamege;
	float attackTime;

	Combat(float health = 100.0f, float attackDamege = 10.0f, float attackTime = 500.0f);

	void TakeDamage(float damage);
	float DealDamage() const;
	bool IsDead() const;

};