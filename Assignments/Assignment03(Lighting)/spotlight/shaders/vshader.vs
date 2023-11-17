#version 330 core

in vec3 vVertex;
in vec3 vNormal;


uniform mat4 vModel;
uniform mat4 vView;
uniform mat4 vProjection;


uniform vec3 lpos_world;
uniform vec3 eye_normal;
uniform vec3 direction;

out vec3 n;
out vec3 e;
out vec3 l;
out vec3 spot_direction;



void main() {
	gl_Position = vProjection * vView * vModel * vec4(vVertex, 1.0);
	//fColor = vColor; //Interpolate color
	n = vNormal;
    l = normalize(lpos_world - vec3(vModel*vec4(vVertex,1.0)));
    e = vec3(vModel*vec4(eye_normal,1.0));
    // l=normalize(lpos_world-vVertex);
    // e=eye_normal;
    spot_direction=direction;
}
