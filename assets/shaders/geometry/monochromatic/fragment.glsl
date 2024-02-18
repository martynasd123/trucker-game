#version 330 core

flat in uint voMaterialIndex;
in vec3 voPos;
in vec3 voNormal;

layout(location = 0) out vec3 gColor;
layout(location = 1) out vec3 gNormal;
layout(location = 2) out vec3 gPosition;

const int MAX_MATERIALS_PER_OBJECT = 20;

struct Material {
    vec3 specular;
    vec3 color;
    float ambient;
    float diffuse;
    float shininess;
};

layout(std140) uniform ub_materials {
    Material materials[2];
};

void main()
{
    gColor = vec3(materials[voMaterialIndex].color.xyz);
    gNormal = voNormal;
    gPosition = voPos;
}