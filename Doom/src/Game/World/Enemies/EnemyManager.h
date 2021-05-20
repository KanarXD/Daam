#pragma once
#include "Enemy.h"

class EnemyManager
{
private:
	static std::vector<Enemy> enemies;
	static std::unordered_map<Enemy::Type, EnemySpecs> enemiesSpecs;

public:
	static std::shared_ptr<EnemyManager> GetInstance();

	static void Init(const std::unordered_map<Enemy::Type, EnemySpecs>& enemiesSpecification);
	static void Update(float dt);
	static void Destroy();

	static void Add(Enemy::Type enemyType, const Transform& transform);

	static void DrawEnemies();

	static const EnemySpecs& GetEnemySpecs(Enemy::Type enemyType) { return enemiesSpecs.at(enemyType); }

private:
	EnemyManager() = default;
	EnemyManager(EnemyManager const&) = delete;
	void operator=(EnemyManager const&) = delete;
};
