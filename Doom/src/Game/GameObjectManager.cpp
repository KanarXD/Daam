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

bool linesIntersect(glm::vec2 s1, glm::vec2 e1, glm::vec2 s2, glm::vec2 e2)
{
	float M = ((e2.y - s2.y) * (e1.x - s1.x) - (e2.x - s2.x) * (e1.y - s1.y));
	float uA = ((e2.x - s2.x) * (s1.y - s2.y) - (e2.y - s2.y) * (s1.x - s2.x)) / M;
	float uB = ((e1.y - s1.y) * (s1.y - s2.y) - (e1.y - s1.y) * (s1.x - s2.x)) / M;

	return uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1;
}

bool GameObjectManager::Ray(const glm::vec3& from, float rotY, float length, const std::string& type)
{
	glm::vec2 rayStart{ from.x, from.z };
	glm::vec2 rayEnd{ length * sin(rotY) + from.x, length * cos(rotY) + from.z };

	for (auto& gameObject : gameObjects)
	{
		if (gameObject->GetType() == type)
		{
			glm::vec3 center = gameObject->GetTransform().position + gameObject->GetHitbox().offset;
			glm::vec3 size = gameObject->GetTransform().scale * gameObject->GetHitbox().scaleModifier;

			glm::vec2 A{ center.x - size.x, center.z - size.z };
			glm::vec2 B{ center.x + size.x, center.z - size.z };
			glm::vec2 C{ center.x - size.x, center.z + size.z };
			glm::vec2 D{ center.x + size.x, center.z + size.z };

			bool t1 = linesIntersect(rayStart, rayEnd, A, B);
			bool t2 = linesIntersect(rayStart, rayEnd, A, C);
			bool t3 = linesIntersect(rayStart, rayEnd, D, B);
			bool t4 = linesIntersect(rayStart, rayEnd, D, C);
			if (t1 || t2 || t3 || t4) return true;
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
