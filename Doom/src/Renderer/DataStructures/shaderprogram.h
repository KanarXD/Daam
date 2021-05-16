#pragma once

#include "Renderer/Library/Library.h"

class ShaderProgram : public LibraryElement
{
private:
	GLuint shaderProgram; //Uchwyt reprezentujący program cieniujacy
	GLuint vertexShader; //Uchwyt reprezentujący vertex shader
	GLuint geometryShader; //Uchwyt reprezentujący geometry shader
	GLuint fragmentShader; //Uchwyt reprezentujący fragment shader
public:
	ShaderProgram(const std::string& name, const char* vertexShaderFile,const char* geometryShaderFile,const char* fragmentShaderFile);
	~ShaderProgram();

	ShaderProgram(ShaderProgram&& shaderProgram) noexcept;

	void use() const; //Włącza wykorzystywanie programu cieniującego
	GLuint u(const char* variableName) const; //Pobiera numer slotu związanego z daną zmienną jednorodną
	GLuint a(const char* variableName) const; //Pobiera numer slotu związanego z danym atrybutem

private:
	char* readFile(const char* fileName); //metoda wczytująca plik tekstowy do tablicy znaków
	GLuint loadShader(GLenum shaderType, const char* fileName); //Metoda wczytuje i kompiluje shader, a następnie zwraca jego uchwyt
};


