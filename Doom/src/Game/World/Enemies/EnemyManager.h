#pragma once
#include "Enemy.h"
#include "Enemy_Tank.h"

class EnemyManager
{
private:
	static std::vector<Enemy> enemies;
	
public:
	static std::shared_ptr<EnemyManager> GetInstance();

	static void Update(float dt);
	static void Destroy();

	template <class T> static void Add(const Transform& transform);

	static void DrawEnemies();

private:
	EnemyManager() = default;
	EnemyManager(EnemyManager const&) = delete;
	void operator=(EnemyManager const&) = delete;
};

template<class T>
inline void EnemyManager::Add(const Transform& transform)
{
	if (std::is_base_of<Enemy, T>::value)
	{
		enemies.push_back(T(transform));
	}
	else
	{
		LOGERROR("Wrong enemy type");
	}
}
