#include "pch.h"
#include "TextureLibrary.h"
#include "Utility/stb_image.h"

std::shared_ptr<TextureLibrary> TextureLibrary::GetInstance()
{
	static std::shared_ptr<TextureLibrary> textureLibraryInstance(new TextureLibrary());
	return textureLibraryInstance;
}

std::optional<const Texture*> TextureLibrary::Get(const std::string& texturePath) const
{
	auto texture = Library::Get(texturePath);
	if (texture.has_value())
		return texture.value();
	LOGERROR("texture", texturePath, "does not exists!");
	return {};
}

std::optional<const Texture*> TextureLibrary::Load(const std::string& texturePath)
{
	auto texture = FindElement(texturePath);
	if (texture.has_value())
		return texture.value();

	//stbi_set_flip_vertically_on_load(1);
	int32_t width, height, bpp;
	unsigned char* image = stbi_load(texturePath.c_str(), &width, &height, &bpp, 4);

	if (image == nullptr)
	{
		LOGERROR("load texture", texturePath, "read error");
		return {};
	}

	const Texture* tex = InsertData(texturePath, image, width, height);
	stbi_image_free(image);

	return tex;
}


