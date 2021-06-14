#version 330

uniform sampler2D textureMap0;
uniform sampler2D textureMap1;
uniform sampler2D textureMap2;
uniform int isTexture;

uniform vec4 diffuse;
uniform vec4 specular;

uniform int LightSourcesCount;

uniform mat4 V;
uniform mat4 M;

in vec2 iTexCoord0;
in vec4 l[5];

out vec4 pixelColor; 

void main(void) {
	vec4 color;
	if (isTexture > 0) {
		color = texture(textureMap0, iTexCoord0); 
	} else {
		color = diffuse;
	}
	
	vec4 mn = normalize(vec4(texture(textureMap1, iTexCoord0).rgb * 2 - 1, 0));

	float mul = 0.0f;
	for(int i = 0; i < LightSourcesCount; i++) {
		vec4 ml = normalize(l[i]);
		float nl = clamp(dot(mn, ml), 0, 1);
		mul += nl;
    }
	mul = mul / LightSourcesCount + 0.2f;
	pixelColor = vec4(color.rgb * clamp(mul, 0, 1), 1.0f);
}

