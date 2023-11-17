#version 330 core

in vec3 fragColor; // Receive the vertex color with lighting from the vertex shader

out vec4 outColor;

void main(void) {
    outColor = vec4(fragColor, 1.0);
}
