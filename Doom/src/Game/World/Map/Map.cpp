#include "pch.h"
#include "Map.h"

#include "Renderer/Renderer.h"
#include "Game/Player.h"
#include "Game/GameObjectManager.h"


Map::Map(const std::string& name, Params& mapParams)
	: LibraryElement(name), params(std::move(mapParams))
{
	for (const auto& box : params.boxes.boxVector)
	{
		GameObjectManager::Add(Transform(glm::vec3(box.position.x * params.boxes.size, 0, box.position.y * params.boxes.size)), "box");
	}
}

void Map::Draw() const
{
	for (const Box& box : params.boxes.boxVector)
	{
		Renderer::DrawMesh(params.boxes.mesh, glm::translate(params.boxes.matrix, glm::vec3(box.position.x , 0, box.position.y)), params.boxes.shader);
	}

	static glm::mat4 SurfaceMatrix = glm::rotate(glm::mat4(1.0f), Consts::PI / 2.0f, glm::vec3(1, 0, 0));

	Renderer::DrawMesh(params.surface.mesh, SurfaceMatrix, params.surface.shader);
	Renderer::DrawCubeMap(params.skybox);
}

void Map::CheckPlayerColisions() const
{
	Transform& pt = Player::GetTransform();
	int id = 0;
	for (const Box& box : params.boxes.boxVector)
	{
		if (pt.position.x - pt.scale.x < box.position.x * params.boxes.size + params.boxes.size / 2.0f &&
			pt.position.x + pt.scale.x > box.position.x * params.boxes.size - params.boxes.size / 2.0f &&
			pt.position.z - pt.scale.z < box.position.y * params.boxes.size + params.boxes.size / 2.0f &&
			pt.position.z + pt.scale.z > box.position.y * params.boxes.size - params.boxes.size / 2.0f)
		{
			float distX = pt.position.x - box.position.x * params.boxes.size;
			float distZ = pt.position.z - box.position.y * params.boxes.size;

			if (fabs(distX) > fabs(distZ))
			{
				if (distX < 0)
					pt.position = glm::vec3(box.position.x * params.boxes.size - params.boxes.size / 2.0f - pt.scale.x, pt.position.y, pt.position.z);
				else
					pt.position = glm::vec3(box.position.x * params.boxes.size + params.boxes.size / 2.0f + pt.scale.x, pt.position.y, pt.position.z);
			}
			else
			{
				if (distZ < 0)
					pt.position = glm::vec3(pt.position.x, pt.position.y, box.position.y * params.boxes.size - params.boxes.size / 2.0f - pt.scale.z);
				else
					pt.position = glm::vec3(pt.position.x, pt.position.y, box.position.y * params.boxes.size + params.boxes.size / 2.0f + pt.scale.z);
			}

			// LOGTRACE("collision player pos: ", pt.position.x, pt.position.z);
			// LOGTRACE("box id: ", id, "pos: ", box.position.x, box.position.y);
		}

		id++;
	}
}

std::vector<Vertex>& Map::GetPlaneVertexes(float width, float height, float size) {
	static std::vector<Vertex> vertexes;
	vertexes = {
		{  2 * width / 2.0f - size / 2.0f,  2 * height / 2.0f - size / 2.0f, 0, 0, 0, 0, 0, 0, 0,  1 * width / 2.0f / size ,  1 * height / 2.0f / size },
		{  0 * width / 2.0f - size / 2.0f,  2 * height / 2.0f - size / 2.0f, 0, 0, 0, 0, 0, 0, 0, -1 * width / 2.0f / size ,  1 * height / 2.0f / size },
		{  2 * width / 2.0f - size / 2.0f,  0 * height / 2.0f - size / 2.0f, 0, 0, 0, 0, 0, 0, 0,  1 * width / 2.0f / size , -1 * height / 2.0f / size },
		{  0 * width / 2.0f - size / 2.0f,  0 * height / 2.0f - size / 2.0f, 0, 0, 0, 0, 0, 0, 0, -1 * width / 2.0f / size , -1 * height / 2.0f / size }
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

std::vector<Vertex>& Map::GetCubeVertexes() {
	static std::vector<Vertex> vertexes;
	vertexes = {
		{ -0.5f, 0.0f,  0.5f, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f },
		{  0.5f, 0.0f,  0.5f, 0, 0, 0, 0, 0, 0, 1.0f, 0.0f },
		{  0.5f, 1.0f,  0.5f, 0, 0, 0, 0, 0, 0, 1.0f, 1.0f },
		{ -0.5f, 1.0f,  0.5f, 0, 0, 0, 0, 0, 0, 0.0f, 1.0f },
	    { -0.5f, 1.0f, -0.5f, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f },
		{  0.5f, 1.0f, -0.5f, 0, 0, 0, 0, 0, 0, 1.0f, 0.0f },
		{  0.5f, 0.0f, -0.5f, 0, 0, 0, 0, 0, 0, 1.0f, 1.0f },
		{ -0.5f, 0.0f, -0.5f, 0, 0, 0, 0, 0, 0, 0.0f, 1.0f },
	    {  0.5f, 0.0f,  0.5f, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f },
		{  0.5f, 0.0f, -0.5f, 0, 0, 0, 0, 0, 0, 1.0f, 0.0f },
		{  0.5f, 1.0f, -0.5f, 0, 0, 0, 0, 0, 0, 1.0f, 1.0f },
		{  0.5f, 1.0f,  0.5f, 0, 0, 0, 0, 0, 0, 0.0f, 1.0f },
	    { -0.5f, 0.0f, -0.5f, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f },
		{ -0.5f, 0.0f,  0.5f, 0, 0, 0, 0, 0, 0, 1.0f, 0.0f },
		{ -0.5f, 1.0f,  0.5f, 0, 0, 0, 0, 0, 0, 1.0f, 1.0f },
		{ -0.5f, 1.0f, -0.5f, 0, 0, 0, 0, 0, 0, 0.0f, 1.0f }
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
