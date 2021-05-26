#include "pch.h"

#include "Window.h"
#include "Renderer/Renderer.h"
#include "Game/Player.h"


std::shared_ptr<Window> Window::GetInstance()
{
	static std::shared_ptr<Window> WindowInstance(new Window());
	return WindowInstance;
}

void Window::Create(const std::string& title, uint32_t width, uint32_t height)
{
	if (this->window != nullptr)
	{
		LOGWARNING("Window already created");
		return;
	}
	this->title = title;
	this->width = width;
	this->height = height;

	if (!glfwInit()) { //Zainicjuj bibliotekê GLFW
		LOGERROR("Nie mo¿na zainicjowaæ GLFW.");
		exit(EXIT_FAILURE);
	}

	this->window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!this->window) //Je¿eli okna nie uda³o siê utworzyæ, to zamknij program
	{
		LOGERROR("Nie mo¿na utworzyæ okna.");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(this->window); //Od tego momentu kontekst okna staje siê aktywny i polecenia OpenGL bêd¹ dotyczyæ w³aœnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekê GLEW
		LOGERROR("Nie mo¿na zainicjowaæ GLEW.");
		exit(EXIT_FAILURE);
	}

	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	LOGINFO("OPENGL VERSION:", glGetString(GL_VERSION));

	glfwSetWindowSizeCallback(this->window, WindowResizeCallback);
	glfwSetErrorCallback(ErrorCallbackGLFW);
	glDebugMessageCallback(ErrorCallbackOpenGL, nullptr);
}

Window::~Window()
{
	glfwDestroyWindow(this->window); //Usuñ kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajête przez GLFW
	exit(EXIT_SUCCESS);
}

bool Window::WindowShouldClose() const {
	return glfwWindowShouldClose(window);
}

void Window::SetWindowShouldClose() {
	glfwSetWindowShouldClose(window, true);
}

void Window::SwapBuffers() const {
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Window::WindowResizeCallback(GLFWwindow* window, int width, int height) {
	LOGINFO("WindowResizeCallback", width, height);

	if (height == 0) return;

	auto myWindow = Window::GetInstance();
	myWindow->aspectRatio = (float)width / (float)height;
	myWindow->SetWidth(width);
	myWindow->SetHeight(height);

	Renderer::SetProjection(Player::GetInstance()->GetCamera(), Window::GetInstance()->aspectRatio);
	glViewport(0, 0, width, height);
}

void Window::ErrorCallbackGLFW(int error, const char* description)
{
	LOGERROR("GLWF", error, description);
}

void Window::ErrorCallbackOpenGL(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	LOGERROR("OpenGL", source, type, id, severity, length, message);
}
