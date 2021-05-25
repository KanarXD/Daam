#pragma once

class Window
{
private:
	GLFWwindow* window = nullptr;
	std::string title = "";
	uint32_t width = 0;
	uint32_t height = 0;
	float aspectRatio = 1.0f;
public:
	static std::shared_ptr<Window> GetInstance();

	~Window();

	void Create(const std::string& title, uint32_t width, uint32_t height);

	inline GLFWwindow* GetGLFWwindow() const { return window; }
	inline const std::string& GetTitle() const { return title; }
	inline uint32_t GetWidth() const { return width; }
	inline uint32_t GetHeight() const { return height; }
	inline float GetAspectRatio() const { return aspectRatio; }

private:
	static void WindowResizeCallback(GLFWwindow* window, int width, int height);
	static void ErrorCallbackGLFW(int error, const char* description);
	static void ErrorCallbackOpenGL(GLenum source, GLenum type,GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
};

