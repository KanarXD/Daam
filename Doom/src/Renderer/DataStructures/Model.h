#pragma once

#include "Mesh.h"
#include "assimp/scene.h"


class Model
{
private:
	const ShaderProgram* shaderProgram;
	std::vector<Mesh> meshVector;
	std::string directory;
public:
	Model(const std::string& modelPath, const std::string& shaderName);

	Model(const std::string& modelPath, const std::string& shaderName, const std::vector<std::pair<uint32_t, const std::string> >& texturePathVector);
	
	~Model();

	const ShaderProgram* GetShaderProgram() const { return shaderProgram; }

	void DrawMeshes() const;

private:
	void loadModel(const std::string& modelPath);

	void processNode(aiNode* node, const aiScene* scene);

	void processMesh(aiMesh* mesh, const aiScene* scene);
};

