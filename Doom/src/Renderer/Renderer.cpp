#include "pch.h"
#include "Renderer.h"


glm::mat4 Renderer::P(1.0f);
glm::mat4 Renderer::V(1.0f);

void Renderer::SetProjection(float aspectRatio)
{
	P = glm::perspective(50.0f * consts::PI / 180.0f, aspectRatio, 0.01f, 500.0f);
}

void Renderer::SetCamera(const Camera* camera)
{
	V = glm::lookAt(camera->GetPosition(), camera->GetLootAtPosition(), glm::vec3(0.0f, 1.0f, 0.0f));
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

void Renderer::Draw(VertexArray& vertexArray, uint32_t indicesCount, ShaderProgram& shaderProgram, const glm::mat4& M)
{
	shaderProgram.use();
	vertexArray.Bind();

	glUniformMatrix4fv(shaderProgram.u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(shaderProgram.u("V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(shaderProgram.u("M"), 1, false, glm::value_ptr(M));

	glDrawElements(GL_TRIANGLES, (GLsizei)indicesCount, GL_UNSIGNED_INT, 0);
}
