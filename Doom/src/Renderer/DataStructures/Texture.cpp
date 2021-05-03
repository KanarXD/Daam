#include "pch.h"
#include "Texture.h"

Texture::~Texture()
{
	glDeleteTextures(1, &textureId);
}

Texture::Texture(const std::string& filePath, unsigned char* image, uint32_t width, uint32_t height)
	: LibraryElement(filePath), width(width), height(height)
{
	glGenTextures(1, &textureId); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, textureId); //Uaktywnij uchwyt

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//Wczytaj obrazek do pamiêci KG skojarzonej z uchwytem

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, textureId);
}
