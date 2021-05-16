#include "pch.h"
#include "Texture.h"

Texture::~Texture()
{
	glDeleteTextures(1, &textureId);
}

Texture::Texture(Texture&& texture) noexcept
	: LibraryElement(texture.GetName()), textureId(texture.textureId), width(texture.width), height(texture.height)
{
	texture.textureId = 0;
	texture.width = 0;
	texture.height = 0;
}

Texture::Texture(const std::string& filePath, unsigned char* image, uint32_t width, uint32_t height, bool repeat)
	: LibraryElement(filePath), width(width), height(height)
{
	glGenTextures(1, &textureId); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, textureId); //Uaktywnij uchwyt

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (repeat)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	//Wczytaj obrazek do pamiêci KG skojarzonej z uchwytem

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, textureId);
}
