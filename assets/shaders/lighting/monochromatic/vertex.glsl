#version 330 core

layout(location = 0) in vec3 viPos;

out vec3 voPos;

void main() {
    gl_Position = vec4(viPos, 1.0);
    voPos = viPos;
}