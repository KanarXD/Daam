#pragma once

#include "Renderer/Library/Library.h"

class Texture : public LibraryElement
{
private:
	uint32_t textureId = 0;
	uint32_t width = 0, height = 0;
public:
	Texture(const std::string& filePath, unsigned char* image, uint32_t width, uint32_t height, bool repeat);
	~Texture();

	Texture(Texture&& texture) noexcept;

	uint32_t GetId() const { return textureId; }

	void Bind() const;

};

