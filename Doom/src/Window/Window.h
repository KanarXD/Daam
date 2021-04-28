#pragma once

class Window
{
private:
	static GLFWwindow* window;
	static std::string title;
	static uint32_t width;
	static uint32_t height;
	static float aspectRatio;

public:
	static void Create(const std::string& title, uint32_t width, uint32_t height);

	static void Destroy();

	static inline GLFWwindow* GetGLFWwindow() { return window; }

	static const std::string& GetTitle() { return title; }

	static inline uint32_t GetWidth() { return width; }

	static inline uint32_t GetHeight() { return height; }

	static inline float GetAspectRatio() { return aspectRatio; }

private:
	static void WindowResizeCallback(GLFWwindow* window, int width, int height);
};

