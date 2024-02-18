#version 330 core

layout(location = 0) in vec3 viPos;
layout(location = 1) in vec3 viNormal;
layout(location = 2) in vec2 viUVCoord;
layout(location = 3) in uint viMaterialIndex;

flat out uint voMaterialIndex;
out vec3 voPos;
out vec3 voNormal;

uniform mat4 u_model_to_world;
uniform mat4 u_world_to_clip;

void main() {
    vec4 world = u_model_to_world * vec4(viPos.xyz, 1.0);
    voPos = (world / world.w).xyz;
    gl_Position = u_world_to_clip * world;
    voMaterialIndex = viMaterialIndex;
    voNormal = (u_model_to_world * vec4(viNormal, 1.0f)).xyz;
}