#pragma once

#include "Wave.h"
#include "../../Components/Transform.h"

class Spawner
{
public:
	const static std::string modelPath;

private:
	struct Portal
	{
		glm::vec3 basePos;
		float rotInner{};
		float rotOuter{};
		const static Transform inner;
		const static Transform outer;

		Portal(const glm::vec3& basePos) : basePos(basePos) {}
	};

	const static std::vector<Wave> waves;
	static int currentWaveIter;
	static Wave currentWave;
	
	static std::vector<Portal> portals;


	static int spawnedEnemies;
	static int killedEnemies;
	
	static double timer;
	static double lastSpawnTime;

public:
	static std::shared_ptr<Spawner> GetInstance();
	static void Update(float dt);
	static void Draw();
	static void Destroy();

	static void SpawnEnemy();
	static void EnemyKilled() { killedEnemies++; }
	static bool NewWave();

	static void AddSpawnLocation(const glm::vec2& spawnLocation) { portals.push_back(Portal(glm::vec3(spawnLocation.x, 10, spawnLocation.y))); }
	static void ClearLocations() { portals.clear(); }

private:
	Spawner() = default;
	Spawner(Spawner const&) = delete;
	void operator=(Spawner const&) = delete;

};

