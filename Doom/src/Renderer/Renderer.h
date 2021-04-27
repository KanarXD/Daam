#pragma once

#include "DataStructures/VertexArray.h"
#include "DataStructures/Model.h"
#include "Renderer/Camera.h"

class Renderer
{
private:
	static glm::mat4 P;
	static glm::mat4 V;
public:
	static void SetProjection(float aspectRatio);

	static void SetCamera(const Camera& camera);

	static void DrawModel(const Model& model, const glm::mat4& M);

	static void Draw(VertexArray& vertexArray, uint32_t indicesCount, ShaderProgram& shaderProgram, const glm::mat4& M);

};

