#pragma once

#include "Renderer/DataStructures/CubeMap.h"



class Map : public LibraryElement
{
	friend class MapLibrary;
public:
	struct Box
	{
		Vec2 position;
	};
	struct Surface
	{
		float width;
		float height;
		Mesh mesh;
		const ShaderProgram* shader;
	};
	struct Boxes
	{
		float size;
		Mesh mesh;
		const ShaderProgram* shader;
		std::vector<Box> boxVector;
		const glm::mat4 matrix;
	};
	struct Params
	{
		Surface surface;
		Boxes boxes;
		CubeMap skybox;
	};
private:
	Params params;
public:
	Map(const std::string& name, Params& mapParams);

	void Draw() const;

	void CheckPlayerColisions() const;

private:
	static std::vector<Vertex>& GetPlaneVertexes(float width, float height, float size);
	static std::vector<uint32_t>& GetPlaneIndices();

	static std::vector<Vertex>& GetCubeVertexes();
	static std::vector<uint32_t>& GetCubeIndices();
};



