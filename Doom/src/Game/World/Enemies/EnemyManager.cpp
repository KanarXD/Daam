#include "pch.h"
#include "EnemyManager.h"
#include "Game/Components/Hitbox.h"
#include "Renderer/Renderer.h"

std::vector<std::unique_ptr<Enemy>> EnemyManager::enemies{};

std::shared_ptr<EnemyManager> EnemyManager::GetInstance()
{
	static std::shared_ptr<EnemyManager> instance(new EnemyManager());
	return instance;
}

void EnemyManager::Update(float dt)
{
	std::vector<int> toErase;
	for (int i{}; i < enemies.size(); i++)
	{
		if (enemies[i]->GetSpecs().combat.IsDead()) toErase.push_back(i);
		else enemies[i]->Update(dt);
	}

	for (int i : toErase) enemies.erase(enemies.begin() + i);
}

void EnemyManager::Destroy()
{
	enemies.clear();
}

void EnemyManager::DrawEnemies()
{
	for (auto& enemy : enemies)
	{
		std::optional<const Model*> model = ModelsLibrary::GetInstance()->Get(enemy->GetSpecs().modelPath);
		if (!model.has_value())
		{
			LOGERROR("Enemy Get model: ", enemy->GetSpecs().modelPath);
			continue;
		}

		Renderer::DrawModel(*model.value(), enemy->GetM());

		if (Hitbox::IsShowHitbox())
		{
			std::optional<const Model*> hitbox = ModelsLibrary::GetInstance()->Get(Hitbox::GetModelPath());
			if (!hitbox.has_value())
			{
				LOGERROR("Hitbox Get model: ", Hitbox::GetModelPath());
				continue;
			}
			Renderer::DrawModel(*hitbox.value(), enemy->GetSpecs().hitbox.GetM(enemy->GetTransform()));
		}
	}
}
