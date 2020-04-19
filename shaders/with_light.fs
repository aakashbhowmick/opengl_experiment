#version 330 core

in vec3  fragPos;
in vec3  vertexColor;
in vec3  vertexNormal;

out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
    float ambientStrength = 0.1;
    vec3  lightDir = normalize(lightPos - fragPos);
    float diffuseStrength = max(dot(lightDir, vertexNormal), 0.0);
    vec3 light = (ambientStrength + diffuseStrength) * lightColor;
    FragColor = vec4(light * vertexColor, 1.0);
}
