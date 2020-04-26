#version 330 core

in vec3  fragPos;
in vec3  vertexColor;
in vec3  vertexNormal;

out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform mat4 model; 
uniform mat4 view;

void main()
{
    float ambientStrength = 0.4;

    vec3 lightPosModel = vec3(model * view * vec4(lightPos, 1.0));
    vec3  lightDir = normalize(lightPosModel - fragPos);
    float diffuseStrength = max(dot(lightDir, normalize(vertexNormal)), 0.0);
    vec3 light = (ambientStrength + diffuseStrength) * lightColor;
    FragColor = vec4(light * vertexColor, 1.0);
}
