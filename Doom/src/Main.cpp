#include "pch.h"

#include "Window/Window.h"
#include "Renderer/Renderer.h"
#include "Game/Player.h"
#include "Window/Input.h"

#include "Renderer/Library/TextureLibrary.h"
#include "Renderer/Library/ShadersLibrary.h"
#include "Renderer/Library/ModelsLibrary.h"
#include "Game/World/Map/MapLibrary.h"
#include "Game/Components/Transform.h"
#include "Game/World/Enemies/EnemyManager.h"

int main()
{
	Window::Create("DOOM", 800, 600);
	Player::Init(Transform(glm::vec3(10, 0, 15), glm::vec3(0), glm::vec3(1)));
	Input::GetInstance();
	ShadersLibrary::GetInstance()->Load("shaderCT", "res/shaders/v_simple_texture_color.glsl", NULL, "res/shaders/f_simple_texture_color.glsl");
	ShadersLibrary::GetInstance()->Load("shaderD", "res/shaders/v_debug.glsl", NULL, "res/shaders/f_debug.glsl");
	ShadersLibrary::GetInstance()->Load("shaderSkyBox", "res/shaders/v_cube_map.glsl", NULL, "res/shaders/f_cube_map.glsl");
	ShadersLibrary::GetInstance()->Load("shaderT", "res/shaders/v_simple_texture.glsl", NULL, "res/shaders/f_simple_texture.glsl");
	
	ModelsLibrary::GetInstance()->Load("res/models/Enemy1/enemy1.obj", "shaderCT");

	EnemyManager::GetInstance()->Add<Enemy>(Transform(glm::vec3(10, 0, 30)));
	EnemyManager::GetInstance()->Add<Enemy_Tank>(Transform(glm::vec3(20, 5, 30)));

	auto horseModel = ModelsLibrary::GetInstance()->Load("res/models/Horse/Horse.obj", "shaderCT");
	auto offRoadModel = ModelsLibrary::GetInstance()->Load("res/models/OffRoad Car/offroad_car.obj", "shaderCT", {
		{ 0, "Texture/Body.png" },
		{ 1, "Texture/Rim.png" },
		{ 2, "Texture/Rim.png" },
		{ 3, "Texture/Rim.png" },
		{ 4, "Texture/Rim.png" }
	});
	auto person = ModelsLibrary::GetInstance()->Load("res/models/base/Base Mesh sculpt 2.obj", "shaderCT");
	auto sportsCar = ModelsLibrary::GetInstance()->Load("res/models/Car/Car.obj/car.obj", "shaderCT");
	auto map = MapLibrary::GetInstance()->Load("res/maps/map1.txt");
	
	LOGINFO("drawing...");
	glfwSetTime(0); //Zeruj timer
	while (!glfwWindowShouldClose(Window::GetGLFWwindow())) //Tak d�ugo jak okno nie powinno zosta� zamkni�te
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Player::Update((float)glfwGetTime());
		glfwSetTime(0); //Zeruj timer

		Renderer::SetProjection(Player::GetCamera(), Window::GetAspectRatio());
		Renderer::SetCamera(Player::GetCamera());

		float size = 0.01f;

		/*
		Renderer::DrawModel(*horseModel.value(), glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 2.0f, 0)), glm::vec3(size)));
		Renderer::DrawModel(*horseModel.value(), glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 2.0f, 10.0f)), glm::vec3(size)));
		Renderer::DrawModel(*offRoadModel.value(), glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, 1.0f, 0)), glm::vec3(size)));
		Renderer::DrawModel(*person.value(), glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, 0, -10.0f)), glm::vec3(1.0f)));
		Renderer::DrawModel(*sportsCar.value(), glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)), glm::vec3(1.0f)));
		*/

		EnemyManager::Update((float)glfwGetTime());
		EnemyManager::DrawEnemies();

		if (map.has_value())
		{
			map.value()->CheckPlayerColisions();
			map.value()->Draw();
		}

		glfwSwapBuffers(Window::GetGLFWwindow()); //Przerzu� tySlny bufor na przedni
		glfwPollEvents(); //Wykonaj procedury callback w zalezno�ci od zdarze� jakie zasz�y.
	}

	EnemyManager::Destroy();
	Player::Destroy();
	Input::Destroy();
	Window::Destroy();
}