#include "pch.h"

#include "Window.h"
#include "Renderer/Renderer.h"
#include "Game/Player.h"


GLFWwindow* Window::window = nullptr;
std::string Window::title = "";
uint32_t Window::width = 0;
uint32_t Window::height = 0;
float Window::aspectRatio = 1.0f;


void Window::Create(const std::string& title, uint32_t width, uint32_t height)
{
	if (Window::window != nullptr)
	{
		LOGWARNING("Window already created");
		return;
	}
	Window::title = title;
	Window::width = width;
	Window::height = height;

	if (!glfwInit()) { //Zainicjuj bibliotek� GLFW
		fprintf(stderr, "Nie mo�na zainicjowa� GLFW.\n");
		exit(EXIT_FAILURE);
	}

	Window::window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);  //Utw�rz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!Window::window) //Je�eli okna nie uda�o si� utworzy�, to zamknij program
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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	LOGINFO("OPENGL VERSION:", glGetString(GL_VERSION));

	glfwSetWindowSizeCallback(window, WindowResizeCallback);
	glfwSetErrorCallback(ErrorCallbackGLFW);
	glDebugMessageCallback(ErrorCallbackOpenGL, nullptr);

	//Renderer::SetProjection(GetAspectRatio());
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
	Renderer::SetProjection(Player::GetInstance()->GetCamera(), aspectRatio);
	glViewport(0, 0, width, height);
}

void Window::ErrorCallbackGLFW(int error, const char* description)
{
	Log::Error("GLWF", error, description);
}

void Window::ErrorCallbackOpenGL(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	Log::Error("OpenGL", source, type, id, severity, length, message);
}
