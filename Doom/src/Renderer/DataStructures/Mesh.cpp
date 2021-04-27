#include "pch.h"
#include "Mesh.h"

#include "Renderer/Library/TextureLibrary.h"


Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
	: vertexBuffer(vertices.data(), vertices.size() * sizeof(Vertex)), indexBuffer(indices.data(), indices.size())
{
	VertexBufferLayout vbl;
	vbl.Push<float>(4);
	vbl.Push<float>(4);
	vbl.Push<float>(4);
	vbl.Push<float>(2);

	vertexArray.AddBuffer(vertexBuffer, vbl);
	vertexArray.AddBuffer(indexBuffer);

	LOGTRACE("Mesh vertexes: ", vertices.size(), "indices:", indices.size());
}

void Mesh::Bind(const ShaderProgram* shaderProgram) const
{
	vertexArray.Bind();
}


TextureMesh::TextureMesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, const std::vector<std::string>& textureNamesVector)
	: Mesh(vertices, indices)
{
	for (size_t i = 0; i < textureNamesVector.size(); i++)
	{
		textureVector.push_back(TextureLibrary::Get(textureNamesVector[i]));
	}
}

void TextureMesh::Bind(const ShaderProgram* shaderProgram) const
{
	Mesh::Bind(shaderProgram);
	static const char* names[] = { "textureMap0", "textureMap1", "textureMap2", "textureMap3", "textureMap4" };

	for (uint32_t i = 0; i < textureVector.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		textureVector[i]->Bind();
		glUniform1i(shaderProgram->u(names[i]), i);
	}
}

void TextureMesh::AddTexture(const Texture* texture)
{
	textureVector.push_back(texture);
}

ColorMesh::ColorMesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, const glm::vec4& diffuse, const glm::vec4& specular)
	: Mesh(vertices, indices), diffuse(diffuse), specular(specular)
{
}

void ColorMesh::Bind(const ShaderProgram* shaderProgram) const
{
	Mesh::Bind(shaderProgram);
	glUniform4fv(shaderProgram->u("diffuse"), 1, glm::value_ptr(diffuse));
	glUniform4fv(shaderProgram->u("specular"), 1, glm::value_ptr(specular));
}
