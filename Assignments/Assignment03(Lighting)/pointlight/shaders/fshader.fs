#version 330 core

in vec3 n;
in vec3 e;
in vec3 l;
out vec4 outColor;

vec3 Ls = vec3(1.0, 1.0, 1.0);
vec3 Ld = vec3(0.5, 0.8, 0.7);
vec3 La = vec3(0.0, 1.0, 0.1);


vec3 ks = vec3(1.0, 1.0, 1.0);
vec3 kd = vec3(0.5, 0.6, 0.4);
vec3 ka = vec3(1.0, 1.0, 1.0);


float spec_exp = 32;

// Calculate ambient light component (Ia)
vec3 Ia = La * ka;

// Calculate diffuse light component (Id)
vec3 L = normalize(l);
vec3 N = normalize(n);
float diffuseFactor = max(dot(N, L), 0.0);
vec3 Id = Ld * kd * diffuseFactor;

// Calculate specular light component (Is)
vec3 R = reflect(-L, N);
vec3 V = normalize(e);
vec3 H = normalize(L+V);

float specularFactor = pow(max(dot(n, H), 0.0), spec_exp);
vec3 Is = Ls * ks * specularFactor;

//ambient
// vec3 fColor = Ia ;

//diffuse
// vec3 fColor = Id; 

//specular
// vec3 fColor = Is;

//ambient + diffuse
// vec3 fColor = Ia + Id; 

//ambient + diffuse + specular 
vec3 fColor = Ia + Id + Is;  

void main(void) {
    outColor = vec4(fColor, 1.0);
}
