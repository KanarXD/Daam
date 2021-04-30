#include "pch.h"
#include "Input.h"
#include "Window/Window.h"
#include "Renderer/Camera.h"

Input* Input::instance = nullptr;

Input* Input::GetInstance(float mouseSensitivity) 
{
	if (instance == nullptr) instance = new Input(mouseSensitivity);
	return instance;
}

void Input::Destroy() 
{
	delete instance;
}

Input::Input(float mouseSensitivity) 
{
	this->mouseSensitivity = mouseSensitivity;
	this->lastMousePosition = glm::vec2(0);
	this->mouseInWindow = false;
	this->mouseFirstTime = true;
	this->pitch = 0;
	this->yaw = 0;
	Setup(Window::GetGLFWwindow());
}


void Input::Setup(GLFWwindow* window)
{
	glfwSetKeyCallback(window, KeyCallback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetCursorEnterCallback(window, CursorEnterCallback);
	glfwSetCursorPosCallback(window, CursorPosCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetScrollCallback(window, ScrollCallback);
}

void Input::Key(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		float mSpeed = 2.5f;
		float rSpeed = 1.0f;
		switch (key) {
		case GLFW_KEY_W:		Camera::GetInstance()->SetMovementStepZ(mSpeed);	break;
		case GLFW_KEY_S:		Camera::GetInstance()->SetMovementStepZ(-mSpeed);	break;
		case GLFW_KEY_A:		Camera::GetInstance()->SetMovementStepX(mSpeed);	break;
		case GLFW_KEY_D:		Camera::GetInstance()->SetMovementStepX(-mSpeed);	break;

		case GLFW_KEY_LEFT:		Camera::GetInstance()->SetRotationStepY(rSpeed);	break;
		case GLFW_KEY_RIGHT:	Camera::GetInstance()->SetRotationStepY(-rSpeed);	break;
		case GLFW_KEY_UP:		Camera::GetInstance()->SetRotationStepX(-rSpeed);	break;
		case GLFW_KEY_DOWN:		Camera::GetInstance()->SetRotationStepX(rSpeed);	break;
		}
	}
	if (action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_W: 
		case GLFW_KEY_S:		Camera::GetInstance()->SetMovementStepZ(0); break;
		case GLFW_KEY_A: 
		case GLFW_KEY_D:		Camera::GetInstance()->SetMovementStepX(0); break;

		case GLFW_KEY_LEFT:
		case GLFW_KEY_RIGHT:	Camera::GetInstance()->SetRotationStepY(0); break;
		case GLFW_KEY_UP:
		case GLFW_KEY_DOWN:		Camera::GetInstance()->SetRotationStepX(0); break;
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

	if (mouseFirstTime) {
		lastMousePosition = glm::vec2(x, y);
		mouseFirstTime = false;
	}

	float xOffset = (x - lastMousePosition.x) * mouseSensitivity;
	float yOffset = (lastMousePosition.y - y) * mouseSensitivity;
	lastMousePosition = glm::vec2(x, y);

	yaw += xOffset;
	pitch += yOffset;

	pitch = glm::clamp(pitch, -89.0f, 89.0f);

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	Camera::GetInstance()->SetFront(glm::normalize(direction));
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
