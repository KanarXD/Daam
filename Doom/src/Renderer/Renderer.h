#pragma once

#include "DataStructures/Model.h"
#include "DataStructures/CubeMap.h"
#include "Renderer/Camera.h"

class Renderer
{
private:
	static glm::mat4 P;
	static glm::mat4 V;
	static float drawDistance;
public:
	static void SetProjection(float aspectRatio);

	static void SetCamera(const Camera& camera);

	static void SetDrawDistance(float value);

	static void DrawModel(const Model& model, const glm::mat4& M);

	static void Draw(VertexArray& vertexArray, uint32_t indicesCount, ShaderProgram& shaderProgram, const glm::mat4& M);

	static void DrawCubeMap(const CubeMap& cubeMap);

};

