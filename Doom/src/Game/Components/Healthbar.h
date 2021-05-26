#pragma once

struct Healthbar
{
	const static std::string modelPath;
	float scaleX{ 1 };
	float offsetY{ 0 };
	float rotY{};
	bool draw{ false };

	Healthbar(float scaleX = 1.0f, float offsetY = 0.0f) : scaleX(scaleX), offsetY(offsetY) {}

};

