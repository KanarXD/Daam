#version 330
//in vec4 color; //kolor zwi¹zany z wierzcho³kiem
//Atrybuty
layout (location = 0) in vec3 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
layout (location = 1) in vec3 normal; //wspolrzedne wierzcholka w przestrzeni modelu
layout (location = 2) in vec3 tangent; //wspolrzedne wierzcholka w przestrzeni modelu
layout (location = 3) in vec2 texCoord0; //wspolrzedne wierzcholka w przestrzeni modelu

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

void main(void) {
    gl_Position=P*V*M*vec4(vertex,1.0f);
}