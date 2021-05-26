#include "pch.h"
#include "Input.h"
#include "Window/Window.h"
#include "Game/Player.h"

std::shared_ptr<Input> Input::GetInstance()
{
	static std::shared_ptr<Input> InputInstance(new Input());
	return InputInstance;
}

void Input::Init(bool enableMouse, float mouseSensitivity)
{
	this->mouseSensitivity = mouseSensitivity;
	Setup(enableMouse, Window::GetInstance()->GetGLFWwindow());
}

void Input::Setup(bool enableMouse, GLFWwindow* window)
{
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
	if (enableMouse)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		glfwSetCursorEnterCallback(window, CursorEnterCallback);
		glfwSetCursorPosCallback(window, CursorPosCallback);
		glfwSetMouseButtonCallback(window, MouseButtonCallback);
		glfwSetScrollCallback(window, ScrollCallback);
	}
}

void Input::Key(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	auto player = Player::GetInstance();
	if (mods == GLFW_MOD_SHIFT) player->SetState(Player::State::Sprint);
	else if (mods == GLFW_MOD_CONTROL) player->SetState(Player::State::Crouch);
	else player->SetState(Player::State::Walk);

	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_W:		player->SetVelocity(true, 0, 1);	break;
		case GLFW_KEY_S:		player->SetVelocity(true, 0, -1);	break;
		case GLFW_KEY_A:		player->SetVelocity(true, 1, 0);	break;
		case GLFW_KEY_D:		player->SetVelocity(true, -1, 0);	break;

		case GLFW_KEY_LEFT:		player->SetAngularVelocity(true, 0, 1);	break;
		case GLFW_KEY_RIGHT:	player->SetAngularVelocity(true, 0, -1);	break;

		case GLFW_KEY_UP:		player->Jump();	break;
		case GLFW_KEY_SPACE:    player->ShootOn(); break;

		case GLFW_KEY_ESCAPE:	player->gameState = Player::GameState::Closed;
		}
	}


	if (action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_W:
		case GLFW_KEY_S:		player->SetVelocity(false, 0, 1); break;
		case GLFW_KEY_A:
		case GLFW_KEY_D:		player->SetVelocity(false, 1, 0); break;

		case GLFW_KEY_LEFT:
		case GLFW_KEY_RIGHT:	player->SetAngularVelocity(false, 0, 1); break;
		
		case GLFW_KEY_SPACE:    player->ShootOff(); break;
		}
	}
}

void Input::CursorEnter(GLFWwindow* window, int entered)
{
	mouseInWindow = entered;
}

void Input::CursorPos(GLFWwindow* window, double x, double y)
{
	if (!mouseInWindow) return;

	rotY += mouseSensitivity * float(x - Window::GetInstance()->GetWidth() / 2);
	
	glfwSetCursorPos(window, Window::GetInstance()->GetWidth() / 2, Window::GetInstance()->GetHeight() /2 );
	rotX = glm::clamp(rotX, -80.0f, 80.0f);

	glm::vec3 direction;
	direction.x = cos(glm::radians(rotY)) * cos(glm::radians(rotX));
	direction.y = sin(glm::radians(rotX));
	direction.z = sin(glm::radians(rotY)) * cos(glm::radians(rotX));

	Player::GetInstance()->LookAt(glm::normalize(direction));
}

void Input::MouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch (button) {}
	}
	if (action == GLFW_RELEASE) {
		switch (button) {}
	}
}

void Input::Scroll(GLFWwindow* window, double xOffset, double yOffset)
{
	if (!mouseInWindow) return;
}
