#include "pch.h"

#include "Mesh.h"

#include "Renderer/Library/TextureLibrary.h"


Mesh::Mesh(void* vertices, uint32_t verticesSize, uint32_t* indices, uint32_t indicesCount)
	: vertexBuffer(vertices, verticesSize), indexBuffer(indices, indicesCount),
	diffuse(1.0f), specular(1.0f), useTextures(false)
{
	VertexBufferLayout vbl;
	vbl.Push<float>(3);
	vbl.Push<float>(3);
	vbl.Push<float>(3);
	vbl.Push<float>(2);

	vertexArray.AddBuffer(vertexBuffer, vbl);
	vertexArray.AddBuffer(indexBuffer);

	//LOGTRACE("Mesh vertexes: ", vertices.size(), "indices:", indices.size());
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
	: Mesh((void*)vertices.data(), uint32_t(vertices.size() * sizeof(Vertex)), indices.data(), uint32_t(indices.size()))
{
}

void Mesh::Bind(const ShaderProgram* shaderProgram) const
{
	vertexArray.Bind();
	glUniform1i(shaderProgram->u("isTexture"), useTextures);
	if (useTextures)
	{
		static const char* names[] = { "textureMap0", "textureMap1", "textureMap2", "textureMap3", "textureMap4" };

		for (uint32_t i = 0; i < textureVector.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			textureVector[i]->Bind();
			glUniform1i(shaderProgram->u(names[i]), i);
		}
	}
	else {
		glUniform4fv(shaderProgram->u("diffuse"), 1, glm::value_ptr(diffuse));
		glUniform4fv(shaderProgram->u("specular"), 1, glm::value_ptr(specular));
	}

}

void Mesh::Draw(const ShaderProgram* shaderProgram) const
{
	Bind(shaderProgram);
	glDrawElements(GL_TRIANGLES, GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
}

void Mesh::AddTexture(const Texture* texture)
{
	this->textureVector.push_back(texture);
}

void Mesh::AddColors(const glm::vec4& diffuse, const glm::vec4& specular)
{
	this->diffuse = diffuse;
	this->specular = specular;
}

void Mesh::SetUseTextures(bool value)
{
	this->useTextures = value;
}
