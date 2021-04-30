#version 330

uniform sampler2D textureMap0;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec2 iTexCoord0;

uniform int isTexture;

uniform vec4 diffuse;
uniform vec4 specular;


void main(void) {
	vec4 color;
	if (isTexture > 0) {
		color = texture(textureMap0, iTexCoord0); //Pobranie koloru
	} else {
		color = diffuse;
	}

	pixelColor = color;
}
