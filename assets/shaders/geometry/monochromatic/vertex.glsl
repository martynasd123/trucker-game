#version 330 core

layout(location = 0) in vec3 viPos;
layout(location = 1) in vec3 viNormal;
layout(location = 2) in vec2 viUVCoord;
layout(location = 3) in uint viMaterialIndex;

flat out uint voMaterialIndex;
out vec3 voNormal;
out vec3 voPosition;

uniform mat4 u_transformation;
uniform mat4 u_modelView;
uniform mat4 u_normal;

void main() {
    vec4 pos = u_transformation * vec4(viPos, 1.0f);
    gl_Position = pos;
    voPosition = pos.xyz / pos.w;

    voMaterialIndex = viMaterialIndex;
    voNormal = mat3(transpose(inverse(u_modelView))) * viNormal;
}