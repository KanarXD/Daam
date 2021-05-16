#include "pch.h"
#include "Renderer.h"


glm::mat4 Renderer::P(1.0f);
glm::mat4 Renderer::V(1.0f);
float Renderer::drawDistance = 300.0f;

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



void Renderer::DrawModel(const Model& model, const glm::mat4& M)
{
	const ShaderProgram* shaderProgram = model.GetShaderProgram();
	shaderProgram->use();

	glUniformMatrix4fv(shaderProgram->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(shaderProgram->u("V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(shaderProgram->u("M"), 1, false, glm::value_ptr(M));

	model.DrawMeshes();
}

void Renderer::DrawMesh(const Mesh& mesh, const glm::mat4& M, const ShaderProgram* shaderProgram)
{
	shaderProgram->use();

	glUniformMatrix4fv(shaderProgram->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(shaderProgram->u("V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(shaderProgram->u("M"), 1, false, glm::value_ptr(M));

	mesh.Draw(shaderProgram);
}



void Renderer::Draw(VertexArray& vertexArray, uint32_t indicesCount, const ShaderProgram* shaderProgram, const glm::mat4& M)
{
	shaderProgram->use();
	vertexArray.Bind();

	glUniformMatrix4fv(shaderProgram->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(shaderProgram->u("V"), 1, false, glm::value_ptr(V));
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
