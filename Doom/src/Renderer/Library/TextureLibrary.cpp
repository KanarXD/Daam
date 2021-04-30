#include "pch.h"
#include "TextureLibrary.h"
#include "Utility/stb_image.h"



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

	int32_t width, height, bpp;
	//stbi_set_flip_vertically_on_load(1);
	unsigned char* image = stbi_load(texturePath.c_str(), &width, &height, &bpp, 4);

	if (image == nullptr)
	{
		LOGERROR("load texture", texturePath, "read error");
		return false;
	}

	textureList.emplace_back(texturePath, image, width, height);
	stbi_image_free(image);

	return true;
}
