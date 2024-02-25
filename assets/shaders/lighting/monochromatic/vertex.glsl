#version 330 core

layout(location = 0) in vec3 viPos;

out vec2 uvCoord;

void main() {
    gl_Position = vec4(viPos.xyz, 1.0);
    uvCoord = (viPos.xy + 1.0f) / 2.0f;
}