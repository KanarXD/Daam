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
        std::string path = directory + texturePath.second;
        TextureLibrary::Load(path);
        const Texture* texture = TextureLibrary::Get(path);
        if (texture != nullptr && texturePath.first < meshVector.size())
        {
            LOGTRACE("Model:", modelPath, "Adding texture to mesh");
            ((TextureMesh*)meshVector[texturePath.first])->AddTexture(texture);
        }
        else
        {
            LOGERROR("texturePathVector ERROR: ", path);;
        }
    }
}

Model::~Model()
{
    for (const Mesh* mesh : meshVector)
    {
        delete mesh;
    }
}

void Model::DrawMeshes() const
{
	for (const Mesh* mesh : meshVector)
	{
		mesh->Bind(shaderProgram);
		glDrawElements(GL_TRIANGLES, (GLsizei)mesh->GetIndicesCount(), GL_UNSIGNED_INT, 0);
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
            mesh->mVertices[i].z,
            1.0f
        };

        // normal vectors
        vertices[i].normal = {
            mesh->mNormals[i].x,
            mesh->mNormals[i].y,
            mesh->mNormals[i].z,
            1.0f
        };

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
        vertices[i].tangent = {
            mesh->mTangents[i].x,
            mesh->mTangents[i].y,
            mesh->mTangents[i].z,
            1.0f
        };
    }

    // process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    std::vector<std::string> textureNames;

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

   
    static aiTextureType TextureTypes[] = { aiTextureType_DIFFUSE,  aiTextureType_NORMALS };
    
    if (mesh->HasTextureCoords(0U))
    {
        for (size_t i = 0; i < 2; i++)
        {
            aiString str;
            material->GetTexture(TextureTypes[i], 0, &str);

            std::string path = directory + str.C_Str();

            TextureLibrary::Load(path);

            if (TextureLibrary::Get(path) != nullptr)
            {
                textureNames.push_back(path);
            }
        }
    }
    
    meshVector.push_back(new TextureMesh(vertices, indices, textureNames));
}




