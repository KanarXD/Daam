#pragma once
#include "Game/Components/Hitbox.h"

struct ModelSpec
{
	Hitbox hitbox;
	std::set<std::string> collideWith;
	std::string modelPath;
	std::string shader;
	ModelSpec(const Hitbox& hitbox, const std::set<std::string>& collideWith, const std::string& modelPath, const std::string& shader)
		: hitbox(hitbox), collideWith(collideWith), modelPath(modelPath), shader(shader) {}
};

const static std::unordered_map<std::string, ModelSpec> GOModels{
	{ "default", { 
		{ glm::vec3(0, 1, 0), glm::vec3(1, 2, 1) },	
		{  }, 
		"res/models/_default/_default.obj" , "shaderCT" } },
	{ "player",	{ 
		{ glm::vec3(0, 2, 0), glm::vec3(1, 2, 1) },
		{ "box", "healthkit", "enemy", "enemy_tank" },
		"", "" } },
	{ "enemy", { 
		{ glm::vec3(0, 0, 0), glm::vec3(1.5f) },
		{ "box", "player", "enemy" , "enemy_fast", "enemy_tank", "enemy_boss" },		
		"res/models/Enemies/enemy.obj", "shaderCT" } },
	{ "enemy_fast", {
		{ glm::vec3(0, 0, 0), glm::vec3(1.5f) },
		{ "box", "player", "enemy" , "enemy_fast", "enemy_tank", "enemy_boss" },
		"res/models/Enemies/enemy_fast.obj", "shaderCT" } },
	{ "enemy_tank",	{ 
		{ glm::vec3(0, 0, 0), glm::vec3(2) }, 
		{ "box", "player", "enemy" , "enemy_fast", "enemy_tank", "enemy_boss" },
		"res/models/Enemies/enemy_tank.obj", "shaderCT" } },
	{ "enemy_boss",	{
		{ glm::vec3(0, 0, 0), glm::vec3(2.5f) },
		{ "box", "player", "enemy" , "enemy_fast", "enemy_tank", "enemy_boss" },
		"res/models/Enemies/enemy_boss.obj", "shaderCT" } },
	{ "healthkit", { 
		{ glm::vec3(0), glm::vec3(0.4f, 0.2f, 0.4f) },	
		{ "player" },
		"res/models/Healthkit/healthkit.obj", "shaderCT" } },
	{ "box", { 
		{ glm::vec3(0, 5, 0), glm::vec3(5.0f), false },
		{ "player", "enemy", "enemy_tank" }, 
		"", "" } }
};
