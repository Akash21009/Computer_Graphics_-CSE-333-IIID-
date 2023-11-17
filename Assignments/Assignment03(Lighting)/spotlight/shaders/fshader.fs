#version 330 core
in vec3 n;
in vec3 e;
in vec3 l; //light direction
in vec3 spot_direction;

vec3 Ls = vec3(1.0, 1.0, 1.0);
vec3 Ld = vec3(0.5, 0.8, 0.7);
vec3 La = vec3(0.0, 0.5, 0.3);

vec3 ks = vec3(1.0, 1.0, 1.0);
vec3 kd = vec3(0.5, 0.6, 0.4);
vec3 ka = vec3(1.0, 1.0, 1.0);

float spec_exp = 32;
float cutOff=1.047;
float outerCutoff=1.1344;
float epsilon,intensity;
//ambient
vec3 Ia = ka*La;

vec3 Id = Ld * kd * max(dot(normalize(n), normalize(l)), 0.0);


vec3 Is = Ls * ks * max(pow(dot(normalize(n), normalize(normalize(l)+normalize(e))), spec_exp),0.0);

float theta=acos(dot(normalize(spot_direction),normalize(-l)));
vec3 fColor;


out vec4 outColor;
void main(void) {

    if(theta<=cutOff){
        fColor= (Ia+Id+Is);
    }
    //soft edges condition
    else if(theta<outerCutoff && theta>cutOff){
        epsilon=cutOff-outerCutoff;
        intensity=(theta-outerCutoff)/(epsilon);
        Id=Id*intensity;
        Is=Is*intensity;
        fColor=(Ia+Id+Is);
    }
    else fColor=(Ia);

    outColor = vec4(fColor, 1.0);
        
}
