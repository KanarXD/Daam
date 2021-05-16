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
	static void SetProjection(const Camera& camera, float aspectRatio);

	static void SetCamera(const Camera& camera);

	static void SetDrawDistance(float value);

	static void DrawModel(const Model& model, const glm::mat4& M);

	static void DrawMesh(const Mesh& mesh, const glm::mat4& M, const ShaderProgram* shaderProgram);

	static void Draw(VertexArray& vertexArray, uint32_t indicesCount, const ShaderProgram* shaderProgram, const glm::mat4& M);

	static void DrawCubeMap(const CubeMap& cubeMap);

};

