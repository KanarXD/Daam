#version 330
//in vec4 color; //kolor związany z wierzchołkiem
//Atrybuty
layout (location = 0) in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
layout (location = 1) in vec4 normal; //wspolrzedne wierzcholka w przestrzeni modelu
layout (location = 2) in vec4 tangent; //wspolrzedne wierzcholka w przestrzeni modelu
layout (location = 3) in vec4 color; //wspolrzedne wierzcholka w przestrzeni modelu

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec4 L;


//Zmienne interpolowane
out vec4 ic;


void main(void) {

    gl_Position=P*V*M*vertex;
}
