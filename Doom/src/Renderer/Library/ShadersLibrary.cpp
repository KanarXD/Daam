#include "pch.h"

#include "ShadersLibrary.h"

std::list<ShaderProgram> ShadersLibrary::shaderProgramList;

const ShaderProgram* ShadersLibrary::Get(const std::string& name)
{
	for (const ShaderProgram& shader : shaderProgramList)
	{
		if (shader.GetName() == name)
		{
			return &shader;
		}
	}
	std::cout << "shader does not exists! \n";
	return nullptr;
}


bool ShadersLibrary::Load(const std::string& name, const char* vertexShaderFile, const char* geometryShaderFile, const char* fragmentShaderFile)
{
	for (const ShaderProgram& shader : shaderProgramList)
	{
		if (shader.GetName() == name)
		{
			std::cout << "shader name exists! \n";
			return false;
		}
	}

	shaderProgramList.emplace_back(name, vertexShaderFile, geometryShaderFile, fragmentShaderFile);
	return true;
}

