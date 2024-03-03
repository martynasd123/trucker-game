#version 330 core

// Constants
const int MAX_NUM_LIGHTS = 20;
const vec3 lightDirection = normalize(vec3(-1.0f, -1.0f, -1.0f));

in vec2 uvCoord;

uniform sampler2D u_gPosition;
uniform sampler2D u_gNormal;
uniform sampler2D u_gAlbedo;
uniform sampler2D u_gMaterial;

uniform uint u_numLights;

struct PointLight {
    vec3 ambient;
    float quadratic;
    vec3 diffuse;
    float linear;
    vec3 specular;
    float constant;
    vec3 position;
};

struct Material {
    float ambient;
    float diffuse;
    float shininess;
};

layout(std140) uniform ub_lights {
    PointLight lights[MAX_NUM_LIGHTS];
};

out vec4 FragColor;

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 albedo, vec3 position, Material mat) {
    vec3 direction = normalize(light.position - position);
    vec3 reflectDir = reflect(-direction, normalize(normal));

    vec3 diffuse = (max(dot(normal, direction), 0.0) * mat.diffuse) * light.diffuse;
    vec3 specular = pow(max(dot(direction, reflectDir), 0.0), mat.shininess) * light.specular;
    vec3 ambient = mat.ambient * light.ambient;

    float distance    = length(light.position - position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    return albedo * ((diffuse + ambient + specular) * attenuation);
}

void main() {
    vec3 albedo = texture(u_gAlbedo, uvCoord).xyz;
    vec3 normal = texture(u_gNormal, uvCoord).xyz;
    vec3 position = texture(u_gPosition, uvCoord).xyz;
    vec3 mat = texture(u_gMaterial, uvCoord).xyz;

    vec3 result = vec3(0.0f);
    for (uint i = uint(0); i < u_numLights; i++) {
        PointLight pLight = lights[i];
        result+=calculatePointLight(pLight, normal, albedo, position, Material(mat.x, mat.y, mat.z));
    }

    FragColor = vec4(result, 1.0f);
}