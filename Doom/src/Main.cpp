#include "pch.h"

#include "Window/Window.h"
#include "Renderer/Renderer.h"

#include "Renderer/Library/TextureLibrary.h"
#include "Renderer/Library/ShadersLibrary.h"
#include "Utility/Log.h"

float speed_x = 0;
float speed_y = 0;
float walk_speed_z = 0;
float walk_speed_x = 0;

//Procedura obs³ugi b³êdów
void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
	if (action == GLFW_PRESS) {
		static const float speed = 10.0f;
		static const float cameraSpeed = 2.0f;
		if (key == GLFW_KEY_LEFT) speed_y = cameraSpeed;
		if (key == GLFW_KEY_RIGHT) speed_y = -cameraSpeed;
		if (key == GLFW_KEY_UP) speed_x = -cameraSpeed;
		if (key == GLFW_KEY_DOWN) speed_x = cameraSpeed;
		if (key == GLFW_KEY_W) walk_speed_z = 2*speed;
		if (key == GLFW_KEY_S) walk_speed_z = -2*speed;
		if (key == GLFW_KEY_A) walk_speed_x = 2*speed;
		if (key == GLFW_KEY_D) walk_speed_x = -2*speed;

	}
	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_LEFT) speed_y = 0;
		if (key == GLFW_KEY_RIGHT) speed_y = 0;
		if (key == GLFW_KEY_UP) speed_x = 0;
		if (key == GLFW_KEY_DOWN) speed_x = 0;
		if (key == GLFW_KEY_W) walk_speed_z = 0;
		if (key == GLFW_KEY_S) walk_speed_z = 0;
		if (key == GLFW_KEY_A) walk_speed_x = 0;
		if (key == GLFW_KEY_D) walk_speed_x = -0;
	}
}

int main()
{
	Window::Create("DOOM", 800, 600);
	TextureLibrary::Init();
	ShadersLibrary::Load("shaderTexture", "res/shaders/vsp.glsl", NULL, "res/shaders/fsp.glsl");
	ShadersLibrary::Load("shaderColor", "res/shaders/v_simplest.glsl", NULL, "res/shaders/f_simplest.glsl");

	Model model2("res/models/OffRoad Car/OFF -Road car  3D Models.obj", "shaderTexture", { 
		{ 0, "Texture/Body.png" },
		{ 1, "Texture/Rim.png" },
		{ 2, "Texture/Rim.png" },
		{ 3, "Texture/Rim.png" },
		{ 4, "Texture/Rim.png" }
		});
	Model model1("res/models/Horse/Horse.obj", "shaderTexture", { { 0, "Texture/map.jpg" }, {0, "Texture/map bump.jpg" } });

	glfwSetKeyCallback(Window::GetGLFWwindow(), keyCallback);


	Camera camera;

	glfwSetTime(0); //Zeruj timer
	LOGINFO("drawing...");
	while (!glfwWindowShouldClose(Window::GetGLFWwindow())) //Tak d³ugo jak okno nie powinno zostaæ zamkniête
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.RotateX(speed_x * (float)glfwGetTime()); 
		camera.RotateY(speed_y * (float)glfwGetTime()); 
		camera.MoveAlong(walk_speed_z * (float)glfwGetTime());
		camera.MoveHorizonally(walk_speed_x * (float)glfwGetTime());
		glfwSetTime(0); //Zeruj timer

		Renderer::SetCamera(camera);

		float size = 0.01f;

		for (int i = 0; i < 50; i++)
		{
			Renderer::DrawModel(model2, glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0, i * 5.0f)), glm::vec3(size, size, size)));
		}

		for (int i = 0; i < 50; i++)
		{
			Renderer::DrawModel(model1, glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 0, i * 5.0f)), glm::vec3(size, size, size)));
		}

		glfwSwapBuffers(Window::GetGLFWwindow()); //Przerzuæ tySlny bufor na przedni
		glfwPollEvents(); //Wykonaj procedury callback w zaleznoœci od zdarzeñ jakie zasz³y.
	}

	Window::Destroy();
}