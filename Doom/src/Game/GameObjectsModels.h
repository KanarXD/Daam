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
		"res/models/_default/_default.obj" , "shaderCTL" } },
	{ "player",	{
		{ glm::vec3(0, 2, 0), glm::vec3(1, 2, 1) },
		{ "box", "healthkit", "enemy" , "enemy_fast", "enemy_tank", "enemy_boss" },
		"", "" } },
	{ "enemy", {
		{ glm::vec3(0, 0, 0), glm::vec3(1.5f) },
		{ "box", "bullet", "player", "enemy" , "enemy_fast", "enemy_tank", "enemy_boss" },
		"res/models/Enemies/enemy.obj", "shaderCTL" } },
	{ "enemy_fast", {
		{ glm::vec3(0, 0, 0), glm::vec3(1.5f) },
		{ "box", "bullet", "player", "enemy" , "enemy_fast", "enemy_tank", "enemy_boss" },
		"res/models/Enemies/enemy_fast.obj", "shaderCTL" } },
	{ "enemy_tank",	{
		{ glm::vec3(0, 0, 0), glm::vec3(2.25f) },
		{ "box", "bullet", "player", "enemy" , "enemy_fast", "enemy_tank", "enemy_boss" },
		"res/models/Enemies/enemy_tank.obj", "shaderCTL" } },
	{ "enemy_boss",	{
		{ glm::vec3(0, 0, 0), glm::vec3(3.25f) },
		{ "box", "bullet", "player", "enemy" , "enemy_fast", "enemy_tank", "enemy_boss" },
		"res/models/Enemies/enemy_boss.obj", "shaderCTL" } },
	{ "healthkit", {
		{ glm::vec3(0), glm::vec3(0.4f, 0.2f, 0.4f) },
		{ "player" },
		"res/models/Powerups/healthkit.obj", "shaderCTL" } },
	{ "bullet", {
		{ glm::vec3(0), glm::vec3(0.05f), false },
		{ "box", "enemy" , "enemy_fast", "enemy_tank", "enemy_boss" },
		"res/models/Bullet/bullet.obj", "shaderCTL" } },
	{ "box", { 
		{ glm::vec3(0, 5, 0), glm::vec3(5.0f), false },
		{ "player", "bullet", "enemy" , "enemy_fast", "enemy_tank", "enemy_boss" },
		"", "" } }
};
