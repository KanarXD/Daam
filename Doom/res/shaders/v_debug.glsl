#version 330
//in vec4 color; //kolor związany z wierzchołkiem
//Atrybuty
layout (location = 0) in vec3 vertex; //wspolrzedne wierzcholka w przestrzeni modelu


//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;


void main(void) {

    gl_Position=P*V*M*vec4(vertex,1.0f);
}
