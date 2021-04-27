#pragma once

#include "Renderer/DataStructures/Texture.h"
#include<string>
#include <list>


class TextureLibrary
{
private:
	static std::list<Texture> textureList;
	static int32_t textureUnits;
public:
	static void Init();

	static const Texture* Get(const std::string& name);

	static bool Load(const std::string& texturePath);
};

