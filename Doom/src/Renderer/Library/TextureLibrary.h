#pragma once

#include "Renderer/DataStructures/Texture.h"
#include <optional>

class TextureLibrary : public Library<Texture>
{
public:
	static std::shared_ptr<TextureLibrary> GetInstance();

	std::optional<const Texture*> Get(const std::string& texturePath) const override;

	std::optional<const Texture*> Load(const std::string& texturePath);

private:
	TextureLibrary() = default;
	TextureLibrary(TextureLibrary const&) = delete;
	void operator=(TextureLibrary const&) = delete;
};

