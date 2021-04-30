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
	LOGERROR("shader does not exists!");
	return nullptr;
}


bool ShadersLibrary::Load(const std::string& name, const char* vertexShaderFile, const char* geometryShaderFile, const char* fragmentShaderFile)
{
	for (const ShaderProgram& shader : shaderProgramList)
	{
		if (shader.GetName() == name)
		{
			LOGWARNING("shader name exists!");
			return false;
		}
	}

	shaderProgramList.emplace_back(name, vertexShaderFile, geometryShaderFile, fragmentShaderFile);
	return true;
}

