#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "shaderprogram.h"

struct Vec2 { float x, y; };
struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, w; };

struct Vertex 
{
	Vec3 position;
	Vec3 normal;
	Vec3 tangent;
	Vec2 textureCoords;
};

class Mesh
{
private:
	VertexBuffer vertexBuffer;
	IndexBuffer indexBuffer;
	VertexArray vertexArray;
	std::vector<const Texture*> textureVector;
	glm::vec4 diffuse;
	glm::vec4 specular;
	bool useTextures;
public:
	Mesh(void* vertices, uint32_t verticesSize, uint32_t* indices, uint32_t indicesCount);

	Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

	uint32_t GetIndicesCount() const { return indexBuffer.GetCount(); }

	void Bind(const ShaderProgram* shaderProgram) const;

	void Draw(const ShaderProgram* shaderProgram) const;

	void AddTexture(const Texture* texture);

	void AddColors(const glm::vec4& diffuse, const glm::vec4& specular);

	void SetUseTextures(bool value);
};


