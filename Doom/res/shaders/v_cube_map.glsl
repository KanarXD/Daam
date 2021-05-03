#version 330

//Atrybuty
layout (location = 0) in vec3 vertex; //wspolrzedne wierzcholka w przestrzeni modelu

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;

//Zmienne interpolowane
out vec3 iTexCoord;

void main(void) {

    iTexCoord = vertex;

    vec4 pos = P*V*vec4(vertex, 1.0f);

    gl_Position=pos.xyww;
}