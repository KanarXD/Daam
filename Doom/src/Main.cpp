#include "pch.h"

#include "Window/Window.h"
#include "Renderer/Renderer.h"
#include "Game/Player.h"
#include "Window/Input.h"

#include "Renderer/Library/TextureLibrary.h"
#include "Renderer/Library/ShadersLibrary.h"


//Procedura obs³ugi b³êdów
void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

int main()
{
	Window::Create("DOOM", 800, 600);
	TextureLibrary::Init();
	Player::Init();
	Input::GetInstance();
	ShadersLibrary::Load("shaderCT", "res/shaders/v_simple_texture_color.glsl", NULL, "res/shaders/f_simple_texture_color.glsl");
	ShadersLibrary::Load("shaderD", "res/shaders/v_debug.glsl", NULL, "res/shaders/f_debug.glsl");

	Model model1("res/models/Horse/Horse.obj", "shaderCT");

	Model model3("res/models/base/Base Mesh sculpt 2.obj", "shaderCT");

	Model model2("res/models/OffRoad Car/offroad_car.obj", "shaderCT", {
		{ 0, "Texture/Body.png" },
		{ 1, "Texture/Rim.png" },
		{ 2, "Texture/Rim.png" },
		{ 3, "Texture/Rim.png" },
		{ 4, "Texture/Rim.png" }
		});

	glfwSetTime(0); //Zeruj timer
	LOGINFO("drawing...");

	LOGWARNING(sizeof(Vertex));

	while (!glfwWindowShouldClose(Window::GetGLFWwindow())) //Tak d³ugo jak okno nie powinno zostaæ zamkniête
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Player::Update((float)glfwGetTime());
		glfwSetTime(0); //Zeruj timer

		Renderer::SetProjection(Player::GetCamera(), Window::GetAspectRatio());
		Renderer::SetCamera(Player::GetCamera());

		float size = 0.01f;

		Renderer::DrawModel(model1, glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 0, 0)), glm::vec3(size)));

		Renderer::DrawModel(model1, glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 0, 10.0f)), glm::vec3(size)));

		Renderer::DrawModel(model2, glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, 0, 0)), glm::vec3(size)));
		//
		Renderer::DrawModel(model3, glm::mat4(1.0f));
		


		glfwSwapBuffers(Window::GetGLFWwindow()); //Przerzuæ tySlny bufor na przedni
		glfwPollEvents(); //Wykonaj procedury callback w zaleznoœci od zdarzeñ jakie zasz³y.
	}

	Player::Destroy();
	Input::Destroy();
	Window::Destroy();
}