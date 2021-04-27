#include "pch.h"
#include "TextureLibrary.h"
#include "Utility/lodepng.h"



std::list<Texture> TextureLibrary::textureList;
int32_t TextureLibrary::textureUnits = 0;

void TextureLibrary::Init()
{
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &textureUnits);
	LOGINFO("texture units: ", textureUnits);
}

const Texture* TextureLibrary::Get(const std::string& texturePath)
{
	for (const Texture& texture : textureList)
	{
		if (texture.GetPath() == texturePath)
		{
			return &texture;
		}
	}
	LOGERROR("texture", texturePath, "does not exists!");
	return nullptr;
}

bool TextureLibrary::Load(const std::string& texturePath)
{
	for (const Texture& texture : textureList)
	{
		if (texture.GetPath() == texturePath)
		{
			LOGWARNING("load texture name:", texturePath, "exists!");
			return false;
		}
	}
	uint32_t width, height;
	std::vector<unsigned char> image;
	unsigned error = lodepng::decode(image, width, height, texturePath);
	if (error)
	{
		LOGERROR("load texture", texturePath, "read error");
		return false;
	}
	textureList.emplace_back(texturePath, image, width, height);
	return true;
}
