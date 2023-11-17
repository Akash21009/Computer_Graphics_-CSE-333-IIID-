#version 330 core

in vec3 vVertex;
in vec3 vNormal;

uniform mat4 vModel;
uniform mat4 vView;
uniform mat4 vProjection;
uniform vec3 lpos_world;
uniform vec3 eye_normal;

out vec3 fragColor; // Pass the vertex color with lighting to the fragment shader

vec3 Ls = vec3(1.0, 1.0, 1.0);
vec3 Ld = vec3(0.7, 0.7, 0.7);
vec3 La = vec3(0.6, 0.3, 0.4);

vec3 ks = vec3(1.0, 1.0, 1.0);
vec3 kd = vec3(0.5, 0.6, 0.4);
vec3 ka = vec3(1.0, 1.0, 1.0);

float spec_exp = 5.0;

void main() {
    vec3 n = normalize(vNormal);
    vec3 l = normalize(lpos_world - vVertex);
    vec3 e = normalize(eye_normal - vVertex);


    // Calculate lighting components at the vertex
    vec3 a = La * ka;

    vec3 L = normalize(l);
    vec3 N = normalize(n);

    vec3 d = Ld * kd * max(dot(N, L), 0.0);
    
    vec3 R = reflect(-L, N);
    vec3 V = normalize(e);

    vec3 s = Ls * ks * pow(max(dot(R, V), 0.0), spec_exp);


    // Suming up the lighting components

    //ambient
    //vec3 vertexColor = a;

    //diffusion
    //vec3 vertexColor = d;

    //specular
    //vec3 vertexColor = s;

    //ambient+diffuse
    //vec3 vertexColor = a+d;

    //ambient+diffusion+specular
    vec3 vertexColor = a + d + s;

    // Pass the vertex color with lighting to the fragment shader
    fragColor = vertexColor;

    gl_Position = vProjection * vView * vModel * vec4(vVertex, 1.0);
}
