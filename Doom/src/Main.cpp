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
#include "Game/Components/Hitbox.h"
#include "Game/GameObjectManager.h"
#include "Game/World/Enemies/Spawner.h"
#include "Game/Arsenal/Bullet.h"

int main()
{
	auto window = Window::GetInstance();
	auto player = Player::GetInstance();
	auto gameObjectManager = GameObjectManager::GetInstance();

	window->Create("DOOM", 800, 600);
	player->SetTransform(Transform(glm::vec3(100.0f, 0, 100.0f), glm::vec3(0), glm::vec3(1)));
	Input::GetInstance()->Init(true);

	ShadersLibrary::GetInstance()->Load("shaderCT", "res/shaders/v_simple_texture_color.glsl", NULL, "res/shaders/f_simple_texture_color.glsl");
	ShadersLibrary::GetInstance()->Load("shaderD", "res/shaders/v_debug.glsl", NULL, "res/shaders/f_debug.glsl");
	ShadersLibrary::GetInstance()->Load("shaderSkyBox", "res/shaders/v_cube_map.glsl", NULL, "res/shaders/f_cube_map.glsl");
	ShadersLibrary::GetInstance()->Load("shaderT", "res/shaders/v_simple_texture.glsl", NULL, "res/shaders/f_simple_texture.glsl");
	ShadersLibrary::GetInstance()->Load("shaderCTL", "res/shaders/v_simple_texture_color_light.glsl", NULL, "res/shaders/f_simple_texture_color_light.glsl");

	for (const auto& goModel : GOModels)
		if (goModel.second.modelPath != "")
			ModelsLibrary::GetInstance()->Load(goModel.second.modelPath, goModel.second.shader);

	Hitbox::showHitbox = false;
	ModelsLibrary::GetInstance()->Load(Hitbox::rdModelPath, "shaderCT");
	ModelsLibrary::GetInstance()->Load(Hitbox::sqModelPath, "shaderCT");
	ModelsLibrary::GetInstance()->Load(Healthbar::modelPath, "shaderCT");
	ModelsLibrary::GetInstance()->Load(Spawner::modelPath, "shaderCTL");

	/*
	auto person = ModelsLibrary::GetInstance()->Load("res/models/base/Base Mesh sculpt 2.obj", "shaderCT");
	auto horseModel = ModelsLibrary::GetInstance()->Load("res/models/Horse/Horse.obj", "shaderCT");
	auto offRoadModel = ModelsLibrary::GetInstance()->Load("res/models/OffRoad Car/offroad_car.obj", "shaderCT", {
		{ 0, "Texture/Body.png" },
		{ 1, "Texture/Rim.png" },
		{ 2, "Texture/Rim.png" },
		{ 3, "Texture/Rim.png" },
		{ 4, "Texture/Rim.png" }
	});
	auto sportsCar = ModelsLibrary::GetInstance()->Load("res/models/Car/Car.obj/car.obj", "shaderCT");
	*/
	auto map = MapLibrary::GetInstance()->Load("res/maps/map1.txt");

	Renderer::AddLightSource({ 300.0f, 200.0f, 300.0f });
	//Renderer::LightSource* ls = Renderer::AddLightSource({100.0f, 100.0f, 100.0f });

	LOGINFO("drawing...");
	glfwSetTime(0);
	float dt = 0;
	while (!window->WindowShouldClose())
	{
		dt = (float)glfwGetTime();
		glfwSetTime(0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		player->Update(dt);
		//ls->position = { player->GetTransform().position.x, player->GetTransform().position.y + 20.0f, player->GetTransform().position.z };

		Renderer::SetProjection(player->GetCamera(), window->GetAspectRatio());
		Renderer::SetCamera(player->GetCamera());


		gameObjectManager->Update(dt);
		gameObjectManager->Draw();
		Spawner::GetInstance()->Update(dt);
		Spawner::GetInstance()->Draw();

		if (map.has_value()) map.value()->Draw();

		window->SwapBuffers();
	}
	glfwDestroyWindow(window->GetGLFWwindow());

	switch (player->gameState)
	{
	case Player::GameState::Closed: 
		std::cout << "~~~~~ Window Closed ~~~~~\n";
		break;
	case Player::GameState::GameOver: 
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~\n        Game Over        \n~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		break;
	case Player::GameState::Win: 
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~\n         You Won         \n~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		break;
	}

}
