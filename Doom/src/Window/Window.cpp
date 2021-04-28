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

	if (!glfwInit()) { //Zainicjuj bibliotek� GLFW
		fprintf(stderr, "Nie mo�na zainicjowa� GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);  //Utw�rz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Je�eli okna nie uda�o si� utworzy�, to zamknij program
	{
		fprintf(stderr, "Nie mo�na utworzy� okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje si� aktywny i polecenia OpenGL b�d� dotyczy� w�a�nie jego.
	glfwSwapInterval(1); //Czekaj na 1 powr�t plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotek� GLEW
		fprintf(stderr, "Nie mo�na zainicjowa� GLEW.\n");
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
	glfwDestroyWindow(window); //Usu� kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zaj�te przez GLFW
	exit(EXIT_SUCCESS);
}

void Window::WindowResizeCallback(GLFWwindow* window, int width, int height) {
	LOGINFO("WindowResizeCallback", width, height);

	if (height == 0) return;
	aspectRatio = (float)width / (float)height;
	Renderer::SetProjection(aspectRatio);
	glViewport(0, 0, width, height);
}