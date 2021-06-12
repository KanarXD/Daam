#version 330
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal; 
layout (location = 2) in vec3 tangent; 
layout (location = 3) in vec2 texCoord0; 

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

uniform int LightSourcesCount;
uniform vec3 LightPositions[5];

out vec2 iTexCoord0;

out vec4 n;
out vec4 l[5];

void main(void) {
    vec4 vertex4 = vec4(vertex, 1.0f);

    n = normalize(V*M*vec4(normal, 0.0f));

    for(int i = 0; i < LightSourcesCount; i++) {
        l[i] = normalize(V*vec4(LightPositions[i],1.0f) - V*M*vertex4);
    }

    iTexCoord0 = texCoord0;
    gl_Position=P*V*M*vertex4;
}
