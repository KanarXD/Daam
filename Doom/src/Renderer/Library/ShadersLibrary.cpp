#include "pch.h"

#include "ShadersLibrary.h"



std::shared_ptr<ShadersLibrary> ShadersLibrary::GetInstance()
{
	static std::shared_ptr<ShadersLibrary> shadersLibraryInstance(new ShadersLibrary());
	return shadersLibraryInstance;
}

std::optional<const ShaderProgram*> ShadersLibrary::Get(const std::string& name) const
{
	auto shaderProgram = FindElement(name);
	if (shaderProgram.has_value())
		return shaderProgram.value();
	LOGERROR("shader does not exists!");
	return {};
}

std::optional<const ShaderProgram*> ShadersLibrary::Load(const std::string& name, const char* vertexShaderFile, const char* geometryShaderFile, const char* fragmentShaderFile)
{
	auto shaderProgram = FindElement(name);
	if (shaderProgram.has_value())
		return shaderProgram.value();

	return InsertData(name, vertexShaderFile, geometryShaderFile, fragmentShaderFile);
}

