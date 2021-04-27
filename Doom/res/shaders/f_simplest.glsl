#version 330

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec4 ic;

void main(void) {


	//pixelColor= vec4(kd.rgb * nl, kd.a) + vec4(ks.rgb*rv, 0);
	pixelColor= vec4(ic);
}
