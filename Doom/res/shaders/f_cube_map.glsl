#version 330

uniform samplerCube textureMap0;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec3 iTexCoord;

void main(void) {

	
	pixelColor = texture(textureMap0, iTexCoord); //Pobranie koloru
}
