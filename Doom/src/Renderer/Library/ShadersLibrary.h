#pragma once
#include "Renderer/DataStructures/shaderprogram.h"

class ShadersLibrary : public Library<ShaderProgram>
{
public:
	static std::shared_ptr<ShadersLibrary> GetInstance();

	std::optional<const ShaderProgram*> Get(const std::string& shaderName) const override;

	std::optional<const ShaderProgram*> Load(const std::string& name, const char* vertexShaderFile, const char* geometryShaderFile, const char* fragmentShaderFile);

private:
	ShadersLibrary() = default;
	ShadersLibrary(ShadersLibrary const&) = delete;
	void operator=(ShadersLibrary const&) = delete;
};

