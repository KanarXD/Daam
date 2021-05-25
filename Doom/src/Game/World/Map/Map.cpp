#include "pch.h"
#include "Map.h"

#include "Renderer/Renderer.h"
#include "Game/Player.h"
#include "Game/GameObjectManager.h"


Map::Map(const std::string& name, Params& mapParams)
	: LibraryElement(name), params(std::move(mapParams)), 
	surfaceMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(mapParams.surface.width / 2.0f, 0, mapParams.surface.height / 2.0f)))
{
	auto gom = GameObjectManager::GetInstance();
	for (const auto& box : params.boxes.boxVector)
	{
		gom->Add(Transform(glm::vec3(box.position.x * params.boxes.size, 0, box.position.y * params.boxes.size)), "box");
	}
}

void Map::Draw() const
{
	for (const Box& box : params.boxes.boxVector)
	{
		Renderer::DrawMesh(params.boxes.mesh, glm::translate(glm::mat4(1.0f),params.boxes.size * glm::vec3(box.position.x , 0, box.position.y)), params.boxes.shader);
	}

	Renderer::DrawMesh(params.surface.mesh, surfaceMatrix, params.surface.shader);
	Renderer::DrawCubeMap(params.skybox);
}

std::vector<Vertex>& Map::GetPlaneVertexes(float width, float height, float size) {
	width /= 2.0f;
	height /= 2.0f;
	static std::vector<Vertex> vertexes;
	vertexes = {
		{  1.0f * height, 0,  1.0f * width, 0, 1.0f, 0, 0, 0, 0,  1.0f * height / size,  1.0f * width / size },
		{ -1.0f * height, 0,  1.0f * width, 0, 1.0f, 0, 0, 0, 0, -1.0f * height / size,  1.0f * width / size },
		{  1.0f * height, 0, -1.0f * width, 0, 1.0f, 0, 0, 0, 0,  1.0f * height / size, -1.0f * width / size },
		{ -1.0f * height, 0, -1.0f * width, 0, 1.0f, 0, 0, 0, 0, -1.0f * height / size, -1.0f * width / size }
	};
	return vertexes;
}

std::vector<uint32_t>& Map::GetPlaneIndices() {
	static std::vector<uint32_t> indices = {
		0, 1, 2,
		1, 2, 3
	};
	return indices;
}

std::vector<Vertex>& Map::GetCubeVertexes(float size) {
	static std::vector<Vertex> vertexes;
	vertexes = {
		{ -0.5f * size, 0.0f * size,  0.5f * size,  0, 0, 1.0f, 0, 0, 0, 0.0f, 0.0f },
		{  0.5f * size, 0.0f * size,  0.5f * size,  0, 0, 1.0f, 0, 0, 0, 1.0f, 0.0f },
		{  0.5f * size, 1.0f * size,  0.5f * size,  0, 0, 1.0f, 0, 0, 0, 1.0f, 1.0f },
		{ -0.5f * size, 1.0f * size,  0.5f * size,  0, 0, 1.0f, 0, 0, 0, 0.0f, 1.0f },
		{ -0.5f * size, 1.0f * size, -0.5f * size,  0, 0, -1.0f, 0, 0, 0, 0.0f, 0.0f },
		{  0.5f * size, 1.0f * size, -0.5f * size,  0, 0, -1.0f, 0, 0, 0, 1.0f, 0.0f },
		{  0.5f * size, 0.0f * size, -0.5f * size,  0, 0, -1.0f, 0, 0, 0, 1.0f, 1.0f },
		{ -0.5f * size, 0.0f * size, -0.5f * size,  0, 0, -1.0f, 0, 0, 0, 0.0f, 1.0f },
		{  0.5f * size, 0.0f * size,  0.5f * size,  1.0f, 0, 0, 0, 0, 0, 0.0f, 0.0f },
		{  0.5f * size, 0.0f * size, -0.5f * size,  1.0f, 0, 0, 0, 0, 0, 1.0f, 0.0f },
		{  0.5f * size, 1.0f * size, -0.5f * size,  1.0f, 0, 0, 0, 0, 0, 1.0f, 1.0f },
		{  0.5f * size, 1.0f * size,  0.5f * size,  1.0f, 0, 0, 0, 0, 0, 0.0f, 1.0f },
		{ -0.5f * size, 0.0f * size, -0.5f * size, -1.0f, 0, 0, 0, 0, 0, 0.0f, 0.0f },
		{ -0.5f * size, 0.0f * size,  0.5f * size, -1.0f, 0, 0, 0, 0, 0, 1.0f, 0.0f },
		{ -0.5f * size, 1.0f * size,  0.5f * size, -1.0f, 0, 0, 0, 0, 0, 1.0f, 1.0f },
		{ -0.5f * size, 1.0f * size, -0.5f * size, -1.0f, 0, 0, 0, 0, 0, 0.0f, 1.0f }
	};
	return vertexes;
}

std::vector<uint32_t>& Map::GetCubeIndices() {
	static std::vector<uint32_t> indices = {
		0,1,2, 0,2,3,
		4,5,6, 4,6,7,
		8,9,10, 8,10,11,
		12,13,14, 12,14,15
	};
	return indices;
}
