#include "pch.h"
#include "Spawner.h"
#include "Game/Player.h"
#include "Enemies.h"
#include "Game/GameObjectManager.h"
#include "Renderer/Renderer.h"
#include "Window/Window.h"

std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<std::mt19937::result_type> dist3(0, 3);

const std::string Spawner::modelPath = "res/models/Portal/portal.obj";

const Transform Spawner::Portal::inner{ glm::vec3(), glm::vec3(0), glm::vec3(1) };
const Transform Spawner::Portal::outer{ glm::vec3(0,-0.5f,0), glm::vec3(0), glm::vec3(1.5f) };

const std::vector<Wave> Spawner::waves{
	{ { 10, 5, 1, 0 },		5 },
	{ { 10, 10, 5, 0 },		4 },
	{ { 10, 10, 10, 1 },	3 },
	{ { 10, 10, 10, 5 },	2 }
};

std::shared_ptr<Spawner> Spawner::GetInstance()
{
	static std::shared_ptr<Spawner> spawnerInstance(new Spawner());
	return spawnerInstance;
}

void Spawner::Update(float dt)
{
	timer += dt;
	for (auto& portal : portals)
	{
		portal.rotInner += dt;
		portal.rotOuter -= dt;
	}
	if (timer - lastSpawnTime > currentWave.timeBetweenSpawns && currentWave.EnemyToSpawnCount())
	{
		SpawnEnemy();
		lastSpawnTime = timer;
	}
	else if (!currentWave.EnemyToSpawnCount())
	{
		NewWave();
	}
}

void Spawner::Draw()
{
	std::optional<const Model*> model = ModelsLibrary::GetInstance()->Get(modelPath);
	if (!model.has_value())
	{
		LOGERROR("Spawner - ModelsLibrary::Get(...) - ", modelPath);
		return;
	}

	for (const auto& portal : portals)
	{
		Renderer::DrawModel(*model.value(),
			glm::scale(glm::rotate(glm::translate(glm::mat4(1.0f), portal.basePos + Portal::inner.position), portal.rotInner, glm::vec3(0, 1, 0)), Portal::inner.scale));
		Renderer::DrawModel(*model.value(),
			glm::scale(glm::rotate(glm::translate(glm::mat4(1.0f), portal.basePos + Portal::outer.position), portal.rotOuter, glm::vec3(0, 1, 0)), Portal::outer.scale));
	}
}

void Spawner::Destroy()
{
	portals.clear();
}

void Spawner::SpawnEnemy()
{
	int enemyType = dist3(rng);
	while (currentWave.enemyToSpawn[enemyType] <= 0) enemyType = dist3(rng);

	std::uniform_int_distribution<std::mt19937::result_type> loc(0, portals.size() - 1);
	int spawnLocation = loc(rng);
	while (glm::distance(glm::vec3(portals[spawnLocation].basePos.x, 2, portals[spawnLocation].basePos.z), Player::GetInstance()->GetTransform().position) < 10)
		spawnLocation = loc(rng);

	currentWave.enemyToSpawn[enemyType]--;

	switch (enemyType)
	{
	case 0: GameObjectManager::GetInstance()->Add<Enemy>(Transform(glm::vec3(portals[spawnLocation].basePos.x, 2, portals[spawnLocation].basePos.z))); break;
	case 1: GameObjectManager::GetInstance()->Add<Enemy_Fast>(Transform(glm::vec3(portals[spawnLocation].basePos.x, 2, portals[spawnLocation].basePos.z))); break;
	case 2: GameObjectManager::GetInstance()->Add<Enemy_Tank>(Transform(glm::vec3(portals[spawnLocation].basePos.x, 2.5f, portals[spawnLocation].basePos.z))); break;
	case 3: GameObjectManager::GetInstance()->Add<Enemy_Boss>(Transform(glm::vec3(portals[spawnLocation].basePos.x, 4, portals[spawnLocation].basePos.z))); break;
	}

	spawnedEnemies++;
}

bool Spawner::NewWave()
{
	if (currentWaveIter + 1 >= waves.size())
	{
		if (killedEnemies == spawnedEnemies)
		{
			Player::GetInstance()->gameState = Player::GameState::Win;
			Window::GetInstance()->SetWindowShouldClose();
		}
		return false;
	}
	if (killedEnemies != spawnedEnemies) return false;
	LOGINFO("Wave", currentWaveIter, "ended");
	LOGINFO("Wave", currentWaveIter + 1, "started");
	currentWaveIter++;
	currentWave = waves[currentWaveIter];

	spawnedEnemies = 0;
	killedEnemies = 0;
	lastSpawnTime = 0;
	return true;
}
