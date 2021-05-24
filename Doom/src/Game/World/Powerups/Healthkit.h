#pragma once
#include "Powerup.h"

class Healthkit : public Powerup
{
public:
	Healthkit(const Transform& transform, const std::string& type = "healthkit");

};

