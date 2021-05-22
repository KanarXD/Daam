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
			if (Hitbox::CollisionDetection(
				gameObjects[i]->GetTransform(), gameObjects[i]->GetHitbox(),
				gameObjects[j]->GetTransform(), gameObjects[j]->GetHitbox()))
			{
				gameObjects[i]->Collision(*gameObjects[j]);
				gameObjects[j]->Collision(*gameObjects[i]);
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

void GameObjectManager::Draw()
{
	for (auto& gameObject : gameObjects)
	{
		gameObject->Draw();
	}
}
