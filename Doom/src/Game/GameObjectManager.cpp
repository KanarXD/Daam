#include "pch.h"
#include "GameObjectManager.h"
#include "Renderer/Renderer.h"
#include "World/Enemies/Enemy.h"

std::vector<std::unique_ptr<GameObject>> GameObjectManager::gameObjects{};

std::shared_ptr<GameObjectManager> GameObjectManager::GetInstance()
{
	static std::shared_ptr<GameObjectManager> instance(new GameObjectManager());
	return instance;
}

void GameObjectManager::Update(float dt)
{
	std::vector<int> toErase;
	for (int i{}; i < gameObjects.size(); i++)
	{
		// Erasing enemies which are dead (TODO: Kill count)
		if (std::is_base_of<Enemy, decltype(gameObjects[i])>::value)
		{
			std::cout << "is enemy\n";
			if (dynamic_cast<Enemy*>(gameObjects[i].get())->GetSpecs().combat.IsDead()) toErase.push_back(i);
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

	// Collisions with player
	for (int i{}; i < gameObjects.size(); i++)
	{
		if (Hitbox::CollisionDetection(gameObjects[i]->GetTransform(), gameObjects[i]->GetHitbox(), Player::GetTransform(), Player::GetHitbox()))
		{
			gameObjects[i]->Collision(GameObject(Player::GetTransform(), "player"));
			Player::Collision(*gameObjects[i]);
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

bool linesIntersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	if (std::max(x1, x2) < std::min(x3, x4)) return false;

	float a1 = (y1 - y2) / (x1 - x2);
	float a2 = (y3 - y4) / (x3 - x4);

	if (a1 == a2) return false;

	float b1 = y1 - a1 * x1;
	float b2 = y3 - a2 * x3;

	float xA = (b2 - b1) / (a1 - a2);

	if (xA < std::max(std::min(x1, x2), std::min(x3, x4)) ||
		xA > std::min(std::max(x1, x2), std::max(x3, x4))) return false;
	
	return true;
}

bool GameObjectManager::Ray(const glm::vec3& from, const glm::vec3& to, const std::string& type)
{
	for (auto& gameObject : gameObjects)
	{
		if (gameObject->GetType() == type)
		{
			glm::vec3 center = gameObject->GetTransform().position + gameObject->GetHitbox().offset;
			glm::vec3 size = gameObject->GetTransform().scale * gameObject->GetHitbox().scaleModifier;

			bool t1 = linesIntersect(from.x, from.z, to.x, to.z, center.x - size.x, center.z - size.z, center.x + size.x, center.z + size.z);
			bool t2 = linesIntersect(from.x, from.z, to.x, to.z, center.x - size.x, center.z + size.z, center.x + size.x, center.z - size.z);
			if (t1 || t2) return true;
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
