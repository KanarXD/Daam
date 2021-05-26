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
	int currentWaveIter{3};
	Wave currentWave{ waves[currentWaveIter] };
	
	std::vector<Portal> portals{};


	int spawnedEnemies{};
	int killedEnemies{};
	
	double timer{};
	double lastSpawnTime{};

public:
	static std::shared_ptr<Spawner> GetInstance();
	void Update(float dt);
	void Draw();
	void Destroy();

	void SpawnEnemy();
	void EnemyKilled() { killedEnemies++; }
	bool NewWave();

	void AddSpawnLocation(const glm::vec2& spawnLocation) { portals.push_back(Portal(glm::vec3(spawnLocation.x, 10, spawnLocation.y))); }
	void ClearLocations() { portals.clear(); }

private:
	Spawner() = default;
	Spawner(Spawner const&) = delete;
	void operator=(Spawner const&) = delete;

};

