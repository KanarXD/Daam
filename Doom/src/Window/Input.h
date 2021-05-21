#pragma once


class Input
{
private:
	static Input* instance;
	glm::vec2 lastMousePosition;
	bool mouseInWindow;
	bool mouseFirstTime;
	float rotX;
	float rotY;
	float mouseSensitivity;

public:
	static Input* GetInstance(bool enableMouse = false, float mouseSensitivity = 0.1f);
	static void Destroy();

private:
	Input(bool enableMouse, float mouseSensitivity);
	void Setup(bool enableMouse, GLFWwindow* window);

	void Key(GLFWwindow* window, int key, int scancode, int action, int mods);
	void CursorEnter(GLFWwindow* window, int entered);
	void CursorPos(GLFWwindow* window, double x, double y);
	void MouseButton(GLFWwindow* window, int button, int action, int mods);
	void Scroll(GLFWwindow* window, double xOffset, double yOffset);

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) { instance->Key(window, key, scancode, action, mods); }
	static void CursorEnterCallback(GLFWwindow* window, int entered) { instance->CursorEnter(window, entered); }
	static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos) { instance->CursorPos(window, xpos, ypos); }
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) { instance->MouseButton(window, button, action, mods); }
	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) { instance->Scroll(window, xoffset, yoffset); }
};

