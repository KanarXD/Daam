#pragma once
#include "GameObjectsModels.h"
#include "GameObject.h"
#include "Player.h"
#include "World/Enemies/Enemies.h"
#include "World/Powerups/Powerups.h"

class GameObjectManager
{
private:
	static std::vector<std::unique_ptr<GameObject>> gameObjects;

public:
	static std::shared_ptr<GameObjectManager> GetInstance();

	static void Update(float dt);
	static void Destroy();

	template <class T> static void Add(const Transform& transform);
	static void Add(const Transform& transform, const std::string& type);
	
	static bool Ray(const glm::vec3& from, float rotY, float length, const std::string& type);

	static void Draw();

private:
	GameObjectManager() = default;
	GameObjectManager(GameObjectManager const&) = delete;
	void operator=(GameObjectManager const&) = delete;
};

template<class T>
inline void GameObjectManager::Add(const Transform& transform)
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
