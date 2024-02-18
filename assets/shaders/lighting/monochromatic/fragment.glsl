#version 330 core

in vec3 voPos;

uniform sampler2D u_gPosition;
uniform sampler2D u_gNormal;
uniform sampler2D u_gAlbedo;

out vec4 FragColor;

vec3 lightDirection = normalize(vec3(-1.0f, -1.0f, -1.0f));

void main() {
    vec2 texCoords = (voPos.xy + 1.0f) / 2.0f;

    vec4 texColor = texture(u_gAlbedo, texCoords);
    vec4 normal = texture(u_gNormal, texCoords);

    float diff = min(1.0f, max(dot(normal.xyz, lightDirection), 0.0) + 0.3f);

    FragColor = vec4(texColor.xyz * diff, 1.0);
}