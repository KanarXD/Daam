#include "pch.h"

#include "Model.h"

Model::Model(const std::string& modelPath, const ShaderProgram* shaderProgram, std::vector<Mesh>& meshVector)
    : LibraryElement(modelPath), shaderProgram(shaderProgram), meshVector(std::move(meshVector))
{
}

void Model::DrawMeshes() const
{
	for (const Mesh& mesh : meshVector)
	{
		mesh.Bind(shaderProgram);
		glDrawElements(GL_TRIANGLES, mesh.GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}
}
