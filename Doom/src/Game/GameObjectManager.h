#pragma once
#include "GameObjectsModels.h"
#include "GameObject.h"
#include "Player.h"
#include "World/Enemies/Enemies.h"
#include "World/Powerups/Powerups.h"

class GameObjectManager
{
private:
	std::vector<std::unique_ptr<GameObject>> gameObjects;
public:
	static std::shared_ptr<GameObjectManager> GetInstance();

	void Update(float dt);
	void Destroy();

	template <class T> void Add(const Transform& transform);
	void Add(const Transform& transform, const std::string& type);
	
	bool Ray(const glm::vec3& from, const glm::vec3& to, const std::string& type);

	void Draw();

private:
	GameObjectManager() = default;
	GameObjectManager(GameObjectManager const&) = delete;
	void operator=(GameObjectManager const&) = delete;
};

template<class T>
void GameObjectManager::Add(const Transform& transform)
{
	if (std::is_base_of<GameObject, T>::value)
	{
		gameObjects.push_back(std::make_unique<T>(transform));
	}
	else
	{
		LOGERROR("Wrong gameObject type");
	}
}
