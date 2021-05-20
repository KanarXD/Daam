#include "pch.h"
#include "EnemyManager.h"
#include "Renderer/Renderer.h"

std::vector<Enemy> EnemyManager::enemies{};
std::unordered_map<Enemy::Type, EnemySpecs> EnemyManager::enemiesSpecs{};

std::shared_ptr<EnemyManager> EnemyManager::GetInstance()
{
	static std::shared_ptr<EnemyManager> instance(new EnemyManager());
	return instance;
}

void EnemyManager::Init(const std::unordered_map<Enemy::Type, EnemySpecs>& enemiesSpecification)
{
	enemiesSpecs = enemiesSpecification;
}

void EnemyManager::Update(float dt)
{
	std::vector<int> toErase;
	for (int i{}; i < enemies.size(); i++)
	{
		if (enemies[i].GetHealth() <= 0) toErase.push_back(i);
	}

	for (int i : toErase) enemies.erase(enemies.begin() + i);
}

void EnemyManager::Destroy()
{
	enemies.clear();
	enemiesSpecs.clear();
}

void EnemyManager::Add(Enemy::Type enemyType, const Transform& transform)
{
	enemies.push_back(Enemy(enemyType, &enemiesSpecs.at(enemyType), transform, enemiesSpecs.at(enemyType).combat.health));
}

void EnemyManager::DrawEnemies()
{
	for (auto& enemy : enemies)
	{
		Renderer::DrawModel(*enemy.GetSpecs()->model, glm::mat4(enemy.GetM()));
	}
}
