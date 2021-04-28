#include "pch.h"

#include "Window/Window.h"
#include "Window/Input.h"
#include "Renderer/Renderer.h"

#include "Renderer/Library/TextureLibrary.h"
#include "Renderer/Library/ShadersLibrary.h"
#include "Utility/Log.h"

//Procedura obs³ugi b³êdów
void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

int main()
{
	Window::Create("DOOM", 800, 600);
	Camera::GetInstance();
	Input::GetInstance();
	TextureLibrary::Init();
	ShadersLibrary::Load("shaderTexture", "res/shaders/vsp.glsl", NULL, "res/shaders/fsp.glsl");
	ShadersLibrary::Load("shaderColor", "res/shaders/v_simplest.glsl", NULL, "res/shaders/f_simplest.glsl");

	Model model1("res/models/Horse/Horse.obj", "shaderTexture", { { 0, "Texture/map.jpg" }, {0, "Texture/map bump.jpg" } });
	Model model2("res/models/OffRoad Car/offroad_car.obj", "shaderTexture", { 
		{ 0, "Texture/Body.png" },
		{ 1, "Texture/Rim.png" },
		{ 2, "Texture/Rim.png" },
		{ 3, "Texture/Rim.png" },
		{ 4, "Texture/Rim.png" }
		});

	glfwSetTime(0); //Zeruj timer
	LOGINFO("drawing...");
	while (!glfwWindowShouldClose(Window::GetGLFWwindow())) //Tak d³ugo jak okno nie powinno zostaæ zamkniête
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Camera::GetInstance()->Update((float)glfwGetTime());

		glfwSetTime(0); //Zeruj timer

		Renderer::SetCamera(Camera::GetInstance());

		float size = 0.01f;

		Renderer::DrawModel(model1, glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 0, 0)), glm::vec3(size, size, size)));
		Renderer::DrawModel(model2, glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3( 0.0f, 0, 0)), glm::vec3(size, size, size)));
		
		glfwSwapBuffers(Window::GetGLFWwindow()); //Przerzuæ tylny bufor na przedni
		glfwPollEvents(); //Wykonaj procedury callback w zaleznoœci od zdarzeñ jakie zasz³y.
	}

	Camera::Destroy();
	Input::Destroy();
	Window::Destroy();
}