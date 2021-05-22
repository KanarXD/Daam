#pragma once
#include "Game/Components/Hitbox.h"

struct ModelSpec
{
	Hitbox hitbox;
	std::string modelPath;
	std::string shader;
	ModelSpec(const Hitbox& hitbox, const std::string& modelPath, const std::string& shader)
		: hitbox(hitbox), modelPath(modelPath), shader(shader) {}
};

const static std::unordered_map<std::string, ModelSpec> GOModels{
	{ "default",		{ { glm::vec3(0, 1, 0), glm::vec3(1, 2, 1) },			"res/models/_default/_default.obj" , "shaderCT" } },
	{ "player",			{ { glm::vec3(0, 2, 0), glm::vec3(1, 2, 1) },			"", "" } },
	{ "enemy",			{ { glm::vec3(0, 3, 0), glm::vec3(1, 3, 1) },			"res/models/base/Base Mesh sculpt 2.obj", "shaderCT" } },
	{ "enemy_tank",		{ { glm::vec3(0, -1, 0), glm::vec3(1.5f, 2.5f, 1.5f) },	"res/models/Enemy1/enemy1.obj", "shaderCT" } },
	{ "healthkit",		{ { glm::vec3(0), glm::vec3(0.2f) },					"res/models/Healthkit/healthkit.obj", "shaderCT" } },
	{ "box",			{ { glm::vec3(0, 5, 0), glm::vec3(5.0f), false },		"", "" } }
};
