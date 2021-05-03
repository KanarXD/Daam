#pragma once
#include "Renderer/DataStructures/Model.h"
#include "assimp/scene.h"

class ModelsLibrary : public Library<Model>
{
public:
	static std::shared_ptr<ModelsLibrary> GetInstance();

	std::optional<const Model*> Get(const std::string& modelName) const override;

	std::optional<const Model*> Load(const std::string& modelPath, const std::string& shaderName);

	std::optional<const Model*> Load(const std::string& modelPath, const std::string& shaderName, const std::vector<std::pair<uint32_t, std::string> >& texturePathVector);

private:
	void LoadModel(const std::string& modelPath, std::vector<Mesh>& meshVector);
	void ProcessNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& meshVector, const std::string& directory);
	void ProcessMesh(aiMesh* mesh, const aiScene* scene, std::vector<Mesh>& meshVector, const std::string& directory);
private:
	ModelsLibrary() = default;
	ModelsLibrary(ModelsLibrary const&) = delete;
	void operator=(ModelsLibrary const&) = delete;
};

