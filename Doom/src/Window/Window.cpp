#include "pch.h"

#include "Window.h"
#include "Renderer/Renderer.h"


GLFWwindow* Window::window = nullptr;
std::string Window::title = "";
uint32_t Window::width = 0;
uint32_t Window::height = 0;
float Window::aspectRatio = 1;

void Window::Create(const std::string& title, uint32_t width, uint32_t height)
{
	Window::title = title;
	Window::width = width;
	Window::height = height;

	if (!glfwInit()) { //Zainicjuj bibliotekê GLFW
		fprintf(stderr, "Nie mo¿na zainicjowaæ GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Je¿eli okna nie uda³o siê utworzyæ, to zamknij program
	{
		fprintf(stderr, "Nie mo¿na utworzyæ okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje siê aktywny i polecenia OpenGL bêd¹ dotyczyæ w³aœnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekê GLEW
		fprintf(stderr, "Nie mo¿na zainicjowaæ GLEW.\n");
		exit(EXIT_FAILURE);
	}

	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	LOGINFO("OPENGL VERSION:", glGetString(GL_VERSION));

	glfwSetWindowSizeCallback(window, WindowResizeCallback);

	Renderer::SetProjection(GetAspectRatio());
}

void Window::Destroy()
{
	glfwDestroyWindow(window); //Usuñ kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajête przez GLFW
	exit(EXIT_SUCCESS);
}

void Window::WindowResizeCallback(GLFWwindow* window, int width, int height) {
	LOGINFO("WindowResizeCallback", width, height);

	if (height == 0) return;
	aspectRatio = (float)width / (float)height;
	Renderer::SetProjection(aspectRatio);
	glViewport(0, 0, width, height);
}