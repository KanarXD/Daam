#pragma once

#include "Mesh.h"
#include "VertexArray.h"
#include "shaderprogram.h"

struct CubeMapVertex
{
    Vec3 position;
};

class CubeMap
{
private:
	VertexBuffer vertexBuffer;
	VertexArray vertexArray;
    const ShaderProgram* shaderProgram;
    uint32_t textureCubeMapId;
public:
    CubeMap(const std::string& directory, std::vector<std::string> facesNames, const std::string& shaderName);

    const ShaderProgram* GetShaderProgram() const { return shaderProgram; }

    void Bind() const;

};

