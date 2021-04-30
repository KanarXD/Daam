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
	Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

	virtual ~Mesh() = default;

	uint32_t GetIndicesCount() const { return indexBuffer.GetCount(); }

	virtual void Bind(const ShaderProgram* shaderProgram) const;
};

class TextureMesh : public Mesh
{
private:
	std::vector<const Texture*> textureVector;
public:
	TextureMesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, const std::vector<std::string>& textureNamesVector);

	void Bind(const ShaderProgram* shaderProgram) const override;

	void AddTexture(const Texture* texture);

	void AddColors(const glm::vec4& diffuse, const glm::vec4& specular);

	void SetUseTextures(bool value);

};


