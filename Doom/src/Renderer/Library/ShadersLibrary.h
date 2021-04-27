#pragma once
#include "Renderer/DataStructures/shaderprogram.h"

class ShadersLibrary
{
private:
	static std::list<ShaderProgram> shaderProgramList;
public:
	static const ShaderProgram* Get(const std::string& name);

	static bool Load(const std::string& name, const char* vertexShaderFile, const char* geometryShaderFile, const char* fragmentShaderFile);
};

