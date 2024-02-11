#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

void main() {
    vec3 factor = vec3(0.1f, 0.1f, 0.1f);
    mat4 scaling = mat4(
            factor.x, 0.0f, 0.0f, 0.0f,
            0.0f, factor.y, 0.0f, 0.0f,
            0.0f, 0.0f, factor.z, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    );
    gl_Position = scaling * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}