#include "pch.h"

#include "Model.h"
#include "Renderer/Library/TextureLibrary.h"
#include "Renderer/Library/ShadersLibrary.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

Model::Model(const std::string& modelPath, const std::string& shaderName)
    : directory(modelPath.substr(0, modelPath.find_last_of("/") + 1))
{
	shaderProgram = ShadersLibrary::Get(shaderName);
	loadModel(modelPath);
}

Model::Model(const std::string& modelPath, const std::string& shaderName, const std::vector<std::pair<uint32_t, const std::string> >& texturePathVector)
    : Model(modelPath, shaderName)
{
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
            TextureLibrary::Load(path);
            const Texture* texture = TextureLibrary::Get(path);
            if (texture != nullptr)
            {
                LOGTRACE("Model:", modelPath, "Adding texture to mesh");
                meshVector[texturePath.first].AddTexture(texture);
                meshVector[texturePath.first].SetUseTextures(true);
            }
            else
            {
                LOGERROR("texturePathVector ERROR: ", path);;
            }
        }
    }

}

void Model::DrawMeshes() const
{
	for (const Mesh& mesh : meshVector)
	{
		mesh.Bind(shaderProgram);
		glDrawElements(GL_TRIANGLES, mesh.GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}
}

void Model::loadModel(const std::string& modelPath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        LOGERROR("Could not load model at ", modelPath, importer.GetErrorString());
		return;
	}


    meshVector.reserve(scene->mNumMeshes);

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        processMesh(scene->mMeshes[node->mMeshes[i]], scene);
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

void Model::processMesh(aiMesh* mesh, const aiScene* scene)
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

                TextureLibrary::Load(path);

                const Texture* texture = TextureLibrary::Get(path);
                if (texture != nullptr)
                {
                    meshVector.back().AddTexture(texture);
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




