#include "pch.h"
#include "Renderer.h"

#define MAXLIGHTS 5

glm::mat4 Renderer::P(1.0f);
glm::mat4 Renderer::V(1.0f);
float Renderer::drawDistance = 300.0f;
std::list<Renderer::LightSource> Renderer::lightSourceList;

void Renderer::SetProjection(const Camera& camera, float aspectRatio)
{
	P = glm::perspective(camera.GetFov(), aspectRatio, camera.GetNearClip(), camera.GetFarClip());
}

void Renderer::SetCamera(const Camera& camera)
{
	V = glm::lookAt(camera.GetTransform().position, camera.GetLootAtPosition(), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Renderer::SetDrawDistance(float value)
{
	drawDistance = value;
}

Renderer::LightSource* Renderer::AddLightSource(Vec3 position)
{
	if (lightSourceList.size() < MAXLIGHTS)
	{
		lightSourceList.push_back({ position });
		return &lightSourceList.back();
	}
	return nullptr;
}

void Renderer::DrawModel(const Model& model, const glm::mat4& M)
{
	const ShaderProgram* shaderProgram = model.GetShaderProgram();
	

	Bind(shaderProgram);
	glUniformMatrix4fv(shaderProgram->u("M"), 1, false, glm::value_ptr(M));

	model.DrawMeshes();
}

void Renderer::DrawMesh(const Mesh& mesh, const glm::mat4& M, const ShaderProgram* shaderProgram)
{
	Bind(shaderProgram);

	glUniformMatrix4fv(shaderProgram->u("M"), 1, false, glm::value_ptr(M));

	mesh.Draw(shaderProgram);
}

void Renderer::Draw(VertexArray& vertexArray, uint32_t indicesCount, const ShaderProgram* shaderProgram, const glm::mat4& M)
{
	Bind(shaderProgram);

	vertexArray.Bind();

	glUniformMatrix4fv(shaderProgram->u("M"), 1, false, glm::value_ptr(M));

	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, nullptr);
}

void Renderer::DrawCubeMap(const CubeMap& cubeMap)
{
	glDepthFunc(GL_LEQUAL);

	cubeMap.Bind();

	const ShaderProgram* shaderProgram = cubeMap.GetShaderProgram();
	
	glm::mat4 view = glm::mat4(glm::mat3(V));

	glUniformMatrix4fv(shaderProgram->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(shaderProgram->u("V"), 1, false, glm::value_ptr(view));
	
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthFunc(GL_LESS);
}

void Renderer::Bind(const ShaderProgram* shaderProgram)
{
	shaderProgram->use();
	glUniformMatrix4fv(shaderProgram->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(shaderProgram->u("V"), 1, false, glm::value_ptr(V));

	static Vec3 positions[MAXLIGHTS];

	GLsizei size = lightSourceList.size();

	int i = 0;
	for (const LightSource& ls : lightSourceList)
	{
		positions[i++] = ls.position;
	}

	glUniform3fv(shaderProgram->u("LightPositions"), size, (const GLfloat*)(positions));
	glUniform1i(shaderProgram->u("LightSourcesCount"), size);
}
