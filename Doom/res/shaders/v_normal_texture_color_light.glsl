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
out vec4 v;
out vec4 l[5];

void main(void) {
    
    vec4 T = normalize(M*vec4(tangent, 0));
    vec4 N = normalize(M*vec4(normal, 0));
    T = normalize(T - dot(T, N) * N);
    vec4 B = normalize(vec4(cross(vec3(N), vec3(T)), 0));

    mat4 invTBN = transpose(mat4(T, B, N, vec4(0,0,0,1)));
    
    vec4 vertex4 = vec4(vertex, 1.0f);
    v = normalize(invTBN * inverse(V*M) * vec4(0, 0, 0, 1) - invTBN * vertex4);

    for(int i = 0; i < LightSourcesCount; i++) {
        l[i] = normalize(invTBN*inverse(M)*vec4(LightPositions[i],1.0f) - invTBN*vertex4);
    }

    iTexCoord0 = texCoord0;
    gl_Position=P*V*M*vertex4;
}
