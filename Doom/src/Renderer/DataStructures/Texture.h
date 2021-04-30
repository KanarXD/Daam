#pragma once
#include <vector>

class Texture
{
private:
	const std::string path;
	uint32_t width = 0, height = 0;
	uint32_t textureId = 0;
public:
	Texture(const std::string& filePath, unsigned char* image, uint32_t width, uint32_t height);
	~Texture();

	const std::string& GetPath() const { return path; }

	uint32_t GetId() const { return textureId; }

	void Bind() const;

};

