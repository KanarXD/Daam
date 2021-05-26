#pragma once


class Input
{
private:
	bool mouseInWindow{ false };
	bool mouseFirstTime{ true };
	float rotX{};
	float rotY{};
	float mouseSensitivity;
public:
	static std::shared_ptr<Input> GetInstance();
	void Init(bool enableMouse = false, float mouseSensitivity = 0.05f);

private:
	void Setup(bool enableMouse, GLFWwindow* window);

	void Key(GLFWwindow* window, int key, int scancode, int action, int mods);
	void CursorEnter(GLFWwindow* window, int entered);
	void CursorPos(GLFWwindow* window, double x, double y);
	void MouseButton(GLFWwindow* window, int button, int action, int mods);
	void Scroll(GLFWwindow* window, double xOffset, double yOffset);

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) { Input::GetInstance()->Key(window, key, scancode, action, mods); }
	static void CursorEnterCallback(GLFWwindow* window, int entered)						 { Input::GetInstance()->CursorEnter(window, entered); }
	static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos)				 { Input::GetInstance()->CursorPos(window, xpos, ypos); }
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)	 { Input::GetInstance()->MouseButton(window, button, action, mods); }
	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)			 { Input::GetInstance()->Scroll(window, xoffset, yoffset); }
};

