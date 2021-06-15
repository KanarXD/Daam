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
in vec4 v;
in vec4 l[5];

out vec4 pixelColor; 

vec2 parallaxTexCoords(vec4 v, vec2 t, float h, float s) {
	if (v.z <= 0) discard;
	
	vec2 ti = -h*v.xy / s;
	float hi = -1 / s;
	
	vec2 tc = t;
	float hc = 1;
	float ht = texture(textureMap2, tc).r;

	while (hc > ht) { 
		tc = tc + ti;
		if (tc.x < 0 || tc.x > 1 || tc.y < 0 || tc.y > 1) discard;
		hc = hc + hi;
		ht = texture(textureMap2, tc).r;
	}

	vec2 tco = tc - ti;
	float hco = hc - hi;
	float hto = texture(textureMap2, tco).r;

	float x = (hco-hto)/(hco-hto-(hc-ht));

    return (1-x)*tco + x * tc;
}

void main(void) {
	vec4 mv = normalize(v);
	vec2 nt = parallaxTexCoords(mv, iTexCoord0, 0.05, 30);

	vec4 color;
	if (isTexture > 0) {
		color = texture(textureMap0, nt); 
	} else {
		color = diffuse;
	}
	
	vec4 mn = normalize(vec4(texture(textureMap1, nt).rgb * 2 - 1, 0));

	float mul = 0.0f;
	for(int i = 0; i < LightSourcesCount; i++) {
		vec4 ml = normalize(l[i]);
		float nl = clamp(dot(mn, ml), 0, 1);
		mul += nl;
    }
	mul = mul / LightSourcesCount + 0.2f;
	pixelColor = vec4(color.rgb * clamp(mul, 0, 1), 1.0f);
}


