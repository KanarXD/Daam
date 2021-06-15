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
	window->Create("DOOM", 800, 600);

	auto shadersLibrary = ShadersLibrary::GetInstance();
	shadersLibrary->Load("shaderD",		 "res/shaders/v_debug.glsl",					  NULL, "res/shaders/f_debug.glsl");
	shadersLibrary->Load("shaderSkyBox", "res/shaders/v_cube_map.glsl",					  NULL, "res/shaders/f_cube_map.glsl");
	shadersLibrary->Load("shaderT",		 "res/shaders/v_texture.glsl",					  NULL, "res/shaders/f_texture.glsl");
	shadersLibrary->Load("shaderCT",	 "res/shaders/v_texture_color.glsl",			  NULL, "res/shaders/f_texture_color.glsl");
	shadersLibrary->Load("shaderCTL",	 "res/shaders/v_texture_color_light.glsl",		  NULL, "res/shaders/f_texture_color_light.glsl");
	shadersLibrary->Load("shaderCTLN",	 "res/shaders/v_texture_color_light_normal.glsl", NULL, "res/shaders/f_texture_color_light_normal.glsl");
	
	auto player = Player::GetInstance();
	player->SetTransform(Transform(glm::vec3(100.0f, 0, 100.0f), glm::vec3(0), glm::vec3(1)));
	
	Input::GetInstance()->Init(true);
	

	auto modelsLibrary = ModelsLibrary::GetInstance();
	for (const auto& goModel : GOModels)
		if (goModel.second.modelPath != "")
			modelsLibrary->Load(goModel.second.modelPath, goModel.second.shader);

	Hitbox::showHitbox = false;
	modelsLibrary->Load(Hitbox::rdModelPath, "shaderCT");
	modelsLibrary->Load(Hitbox::sqModelPath, "shaderCT");
	modelsLibrary->Load(Healthbar::modelPath, "shaderCT");
	modelsLibrary->Load(Spawner::modelPath, "shaderCTL");

	auto gameObjectManager = GameObjectManager::GetInstance();
	auto map = MapLibrary::GetInstance()->Load("res/maps/map1.txt");

	LOGINFO("drawing...");
	glfwSetTime(0);
	float dt = 0;
	while (!window->WindowShouldClose())
	{
		dt = (float)glfwGetTime();

		glfwSetTime(0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		player->Update(dt);

		Renderer::SetProjection(player->GetCamera(), window->GetAspectRatio());
		Renderer::SetCamera(player->GetCamera());
		player->Draw();

		gameObjectManager->Update(dt);
		gameObjectManager->Draw();
		
		Spawner::GetInstance()->Update(dt);
		Spawner::GetInstance()->Draw();

		if (map.has_value()) map.value()->Draw();

		window->SwapBuffers();
	}

	switch (player->gameState)
	{
	case Player::GameState::Closed: 
		std::cout << "\n~~~~~ Window Closed ~~~~~\n";
		break;
	case Player::GameState::GameOver: 
		std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~\n        Game Over        \n~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		break;
	case Player::GameState::Win: 
		std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~\n         You Won         \n~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		break;
	}

	exit(EXIT_SUCCESS);
}
