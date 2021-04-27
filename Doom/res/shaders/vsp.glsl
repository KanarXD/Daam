#version 330
//in vec4 color; //kolor zwi¹zany z wierzcho³kiem
//Atrybuty
layout (location = 0) in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
layout (location = 1) in vec4 normal; //wspolrzedne wierzcholka w przestrzeni modelu
layout (location = 2) in vec4 tangent; //wspolrzedne wierzcholka w przestrzeni modelu
layout (location = 3) in vec2 texCoord0; //wspolrzedne wierzcholka w przestrzeni modelu

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec4 L;

//Zmienne interpolowane
out vec4 l;
out vec4 n;
out vec4 v;
out vec2 iTexCoord0;
out vec2 iTexCoord1;

void main(void) {
//    vec4 lp = L; //pozcyja œwiat³a, przestrzeñ œwiata
//    l = normalize(V * lp - V*M*vertex); //wektor do œwiat³a w przestrzeni oka
//    v = normalize(vec4(0, 0, 0, 1) - V * M * vertex); //wektor do obserwatora w przestrzeni oka
//    n = normalize(V * M * normal); //wektor normalny w przestrzeni oka
//    
//    iTexCoord1 = (n.xy+1)/2;
    iTexCoord0 = texCoord0;

    gl_Position=P*V*M*vertex;
}