#include "pch.h"
#include "GameObjectManager.h"
#include "Renderer/Renderer.h"
#include "World/Enemies/Types/Enemy.h"
#include "World/Enemies/Spawner.h"

std::vector<std::unique_ptr<GameObject>> GameObjectManager::gameObjects{};

template<typename Base, typename T>
inline bool instanceof(const T*)
{
	return std::is_base_of<Base, T>::value;
}

std::shared_ptr<GameObjectManager> GameObjectManager::GetInstance()
{
	static std::shared_ptr<GameObjectManager> instance(new GameObjectManager());
	return instance;
}

void GameObjectManager::Update(float dt)
{
	std::vector<int> toErase;
	std::vector<std::string> enemiesTypes{ "enemy", "enemy_fast", "enemy_tank", "enemy_boss" };
	for (int i{}; i < gameObjects.size(); i++)
	{
		if (std::find(enemiesTypes.begin(), enemiesTypes.end(), gameObjects[i]->GetType()) != enemiesTypes.end())
		{
			if (dynamic_cast<Enemy*>(gameObjects[i].get())->GetSpecs().combat.IsDead())
			{
				toErase.push_back(i);
				Spawner::GetInstance()->EnemyKilled();
			}
			else gameObjects[i]->Update(dt);
		}
		else
		{
			gameObjects[i]->Update(dt);
		}
	}

	for (int i : toErase) gameObjects.erase(gameObjects.begin() + i);

	// Collisions
	for (int i{}; i < gameObjects.size(); i++)
	{
		for (int j = i + 1; j < gameObjects.size(); j++)
		{
			if (gameObjects[i]->GetCollideWith().find(gameObjects[j]->GetType()) != gameObjects[i]->GetCollideWith().end())
			{
				if (Hitbox::CollisionDetection(
					gameObjects[i]->GetTransform(), gameObjects[i]->GetHitbox(),
					gameObjects[j]->GetTransform(), gameObjects[j]->GetHitbox()))
				{
					gameObjects[i]->Collision(*gameObjects[j]);
					gameObjects[j]->Collision(*gameObjects[i]);
				}
			}
		}
	}

	auto player = Player::GetInstance();
	// Collisions with player
	for (int i{}; i < gameObjects.size(); i++)
	{
		if (Hitbox::CollisionDetection(gameObjects[i]->GetTransform(), gameObjects[i]->GetHitbox(), player->GetTransform(), player->GetHitbox()))
		{
			gameObjects[i]->Collision(GameObject(player->GetTransform(), "player"));
			player->Collision(*gameObjects[i]);
		}
	}
}

void GameObjectManager::Destroy()
{
	gameObjects.clear();
}

void GameObjectManager::Add(const Transform& transform, const std::string& type)
{
	gameObjects.push_back(std::make_unique<GameObject>(transform, type));
}

bool GameObjectManager::Raycast(const glm::vec3& from, const glm::vec3& to, const std::string& type)
{
	bool useRound = GOModels.at(type).hitbox.useRound;
	for (auto& gameObject : gameObjects)
	{
		if (gameObject->GetType() == type)
		{
			glm::vec3 center = gameObject->GetTransform().position + gameObject->GetHitbox().offset;
			glm::vec3 size = gameObject->GetTransform().scale * gameObject->GetHitbox().scaleModifier;
			bool hit = false;
			if (useRound) hit = Collisions::RayCastCylinder(from, to, center, size.x);
			else hit = Collisions::RayCastBox(from, to, center, size);
			if (hit) return hit;
		}
	}
	return false;
}

void GameObjectManager::Draw()
{
	for (auto& gameObject : gameObjects)
	{
		gameObject->Draw();
	}
}
