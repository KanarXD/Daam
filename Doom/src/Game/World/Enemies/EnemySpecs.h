#pragma once
#include "pch.h"
#include "Game/Components/Combat.h"
#include "Renderer/Library/ModelsLibrary.h"

struct EnemySpecs
{
	Combat combat;
	const Model* model;
	float fov;
	float viewDist;
	float speed;

	EnemySpecs(Combat combat, const std::string& modelPath, float fov, float viewDist, float speed)
		: combat(combat), fov(fov), viewDist(viewDist), speed(speed)
	{
		std::optional<const Model*> modelTmp = ModelsLibrary::GetInstance()->Get(modelPath);
		if (!modelTmp.has_value())
		{
			LOGERROR("Enemy Get model: ", modelPath);
			model = nullptr;
			return;
		}
		model = modelTmp.value();
	}
};