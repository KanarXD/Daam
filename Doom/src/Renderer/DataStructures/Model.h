#pragma once

#include "Mesh.h"


class Model : public LibraryElement
{
	friend class ModelsLibrary;
private:
	const ShaderProgram* shaderProgram;
	std::vector<Mesh> meshVector;
public:
	Model(const std::string& modelPath, const ShaderProgram* shaderProgram, std::vector<Mesh>& meshVector);

	const ShaderProgram* GetShaderProgram() const { return shaderProgram; }

	void DrawMeshes() const;

};

