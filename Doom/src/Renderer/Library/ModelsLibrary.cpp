#include "pch.h"
#include "ModelsLibrary.h"

#include "TextureLibrary.h"
#include "ShadersLibrary.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"



std::shared_ptr<ModelsLibrary> ModelsLibrary::GetInstance()
{
	static std::shared_ptr<ModelsLibrary> modelsLibraryInstance(new ModelsLibrary());
	return modelsLibraryInstance;
}

std::optional<const Model*> ModelsLibrary::Get(const std::string& modelName) const
{
    auto model = FindElement(modelName);
    if (model.has_value())
        return model.value();
    LOGERROR("model does not exists!");
    return {};
}

std::optional<const Model*> ModelsLibrary::Load(const std::string& modelPath, const std::string& shaderName)
{
    std::optional<const ShaderProgram*> shaderProgram = ShadersLibrary::GetInstance()->Get(shaderName);
    if (!shaderProgram.has_value())
    {
        LOGERROR("ModelsLibrary Get shader: ", shaderName);
        return {};
    }

    std::vector<Mesh> meshVector;
    LoadModel(modelPath, meshVector);
    if (meshVector.size() == 0)
    {
        LOGERROR("Empty model");
        return {};
    }

    return InsertData(modelPath, shaderProgram.value(), meshVector);
}

std::optional<const Model*> ModelsLibrary::Load(const std::string& modelPath, const std::string& shaderName, const std::vector<std::pair<uint32_t, std::string>>& texturePathVector)
{
    std::optional<const ShaderProgram*> shaderProgram = ShadersLibrary::GetInstance()->Get(shaderName);
    if (!shaderProgram.has_value())
    {
        LOGERROR("ModelsLibrary Get shader: ", shaderName);
        return {};
    }

    std::vector<Mesh> meshVector;
    LoadModel(modelPath, meshVector);
    if (meshVector.size() == 0)
    {
        LOGERROR("Empty model");
        return {};
    }

    std::string directory = modelPath.substr(0, modelPath.find_last_of("/") + 1);
    for (auto& texturePath : texturePathVector)
    {
        if (texturePath.first < meshVector.size()) {
            if (texturePath.second == "NOTEXTURE")
            {
                LOGTRACE("Model:", modelPath, "NO TEXTURE");
                meshVector[texturePath.first].SetUseTextures(false);
                continue;
            }
            
            std::string path = directory + texturePath.second;
            std::optional<const Texture*> texture = TextureLibrary::GetInstance()->Load(path);
            if (texture.has_value())
            {
                LOGTRACE("Model:", modelPath, "Adding texture to mesh");
                meshVector[texturePath.first].AddTexture(texture.value());
                meshVector[texturePath.first].SetUseTextures(true);
            }
            else {
                LOGERROR("Model texturePathVector", path);;
            }
        }
    }
    return InsertData(modelPath, shaderProgram.value(), meshVector);
}

void ModelsLibrary::LoadModel(const std::string& modelPath, std::vector<Mesh>& meshVector)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        LOGERROR("Could not load model at ", modelPath, importer.GetErrorString());
        return;
    }
    meshVector.reserve(scene->mNumMeshes);
    std::string directory = modelPath.substr(0, modelPath.find_last_of("/") + 1);

    ProcessNode(scene->mRootNode, scene, meshVector, directory);
}


void ModelsLibrary::ProcessNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& meshVector, const std::string& directory)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        ProcessMesh(scene->mMeshes[node->mMeshes[i]], scene, meshVector, directory);
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene, meshVector, directory);
    }
}

void ModelsLibrary::ProcessMesh(aiMesh* mesh, const aiScene* scene, std::vector<Mesh>& meshVector, const std::string& directory)
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    std::vector<Texture> textures;
    vertices.resize(mesh->mNumVertices);
    indices.reserve(3ULL * mesh->mNumFaces);

    // vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        // position
        vertices[i].position = {
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        };

        // normal vectors
        if (mesh->HasNormals())
        {
            vertices[i].normal = {
            mesh->mNormals[i].x,
            mesh->mNormals[i].y,
            mesh->mNormals[i].z
            };
        }
        else {
            vertices[i].normal = { 0, 0, 0 };
        }

        // textures
        if (mesh->mTextureCoords[0]) {
            vertices[i].textureCoords = {
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y
            };
        }
        else {
            vertices[i].textureCoords = { 0.0f, 0.0f };
        }

        // tangent vector
        if (mesh->HasTangentsAndBitangents())
        {
            vertices[i].tangent = {
                mesh->mTangents[i].x,
                mesh->mTangents[i].y,
                mesh->mTangents[i].z
            };
        }
        else {
            vertices[i].tangent = { 0, 0, 0 };
        }

    }

    // process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    meshVector.emplace_back(vertices, indices);

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    static aiTextureType TextureTypes[] = { aiTextureType_DIFFUSE,  aiTextureType_NORMALS };

    if (mesh->mMaterialIndex >= 0) {

        std::vector<std::string> textureNames;

        for (size_t i = 0; i < 2; i++)
        {
            aiString str;
            material->GetTexture(TextureTypes[i], 0, &str);
            if (strlen(str.C_Str()) > 0)
            {
                std::string path = directory + str.C_Str();

                std::optional<const Texture*> texture = TextureLibrary::GetInstance()->Load(path);
                if (texture.has_value())
                {
                    meshVector.back().AddTexture(texture.value());
                    meshVector.back().SetUseTextures(true);
                }
            }

            aiColor4D diff(1.0f);
            aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diff);

            aiColor4D spec(1.0f);
            aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &spec);

            meshVector.back().AddColors({ diff.r, diff.g, diff.b, diff.a }, { spec.r, spec.g, spec.b, spec.a });

        }
    }
}

