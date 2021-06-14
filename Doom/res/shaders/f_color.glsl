#version 330

out vec4 pixelColor;

uniform vec4 diffuse;
uniform vec4 specular;

void main(void) {
	pixelColor = vec4(diffuse);
}
