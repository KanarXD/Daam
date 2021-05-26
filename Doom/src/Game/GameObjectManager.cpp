#include "pch.h"
#include "GameObjectManager.h"
#include "Renderer/Renderer.h"
#include "World/Enemies/Types/Enemy.h"
#include "Arsenal/Bullet.h"
#include "World/Enemies/Spawner.h"
#include "Utility/Collisions.h"

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
	std::vector<std::string> enemiesTypes{ "enemy", "enemy_fast", "enemy_tank", "enemy_boss" };

	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		if (std::find(enemiesTypes.begin(), enemiesTypes.end(),  (*it).get()->GetType()) != enemiesTypes.end())
		{
			if (dynamic_cast<Enemy*>((*it).get())->GetSpecs().combat.IsDead())
			{
				gameObjects.erase(it--);
				Spawner::GetInstance()->EnemyKilled();
			}
			else (*it).get()->Update(dt);
		}
		else if ((*it).get()->GetType() == "bullet")
		{
			if (dynamic_cast<Bullet*>((*it).get())->IsHit())
			{
				gameObjects.erase(it--);
			}
			else (*it).get()->Update(dt);
		}
		else
		{
			(*it).get()->Update(dt);
		}
	}

	// Collisions
	for (int i{}; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->GetType() == "bullet")
			if (dynamic_cast<Bullet*>(gameObjects[i].get())->IsHit()) continue;

		for (int j = i + 1; j < gameObjects.size(); j++)
		{
			if (gameObjects[j]->GetType() == "bullet")
				if (dynamic_cast<Bullet*>(gameObjects[j].get())->IsHit()) continue;

			if (gameObjects[i]->GetCollideWith().find(gameObjects[j]->GetType()) != gameObjects[i]->GetCollideWith().end())
			{
				if (Hitbox::CollisionDetection(
					gameObjects[i]->GetTransform(), gameObjects[i]->GetHitbox(),
					gameObjects[j]->GetTransform(), gameObjects[j]->GetHitbox()))
				{
					gameObjects[i]->Collision(gameObjects[j]->GetType());
					gameObjects[j]->Collision(gameObjects[i]->GetType());
				}
			}
		}
	}

	auto player = Player::GetInstance();
	// Collisions with player
	for (int i{}; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->GetCollideWith().find("player") != gameObjects[i]->GetCollideWith().end())
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
