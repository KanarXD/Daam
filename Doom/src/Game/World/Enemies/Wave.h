#pragma once
#include "pch.h"

struct Wave
{
	std::array<int, 4> enemyToSpawn;
	float timeBetweenSpawns;

	Wave(const std::array<int, 4>& enemyToSpawn, float timeBetweenSpawns)
		: enemyToSpawn(enemyToSpawn), timeBetweenSpawns(timeBetweenSpawns) {}

	int EnemyToSpawnCount() const { return std::accumulate(enemyToSpawn.begin(), enemyToSpawn.end(), 0); }
};
