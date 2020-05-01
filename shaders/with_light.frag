#version 330 core

in vec3  fragPos;
in vec3  vertexColor;
in vec3  vertexNormal;

out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform mat4 model; 
uniform mat4 view;
uniform vec3 viewing_pos;

void main()
{
    // Ambient
    float ambientStrength = 0.4;

    // Diffuse
    vec3 lightPosModel = vec3(model * view * vec4(lightPos, 1.0));
    vec3  lightDir = normalize(lightPosModel - fragPos);
    float diffuseStrength = max(dot(lightDir, normalize(vertexNormal)), 0.0);

    // Specular
    float specularFactor = 0.5f;
    vec3 view_dir = normalize(viewing_pos - fragPos);
    vec3 reflect_dir = reflect(-lightDir, vertexNormal);
    float spec = pow( max( dot(view_dir, reflect_dir), 0.0), 32);
    float specularStrength = specularFactor * spec;

    vec3 light = (ambientStrength + diffuseStrength + specularStrength) * lightColor;
    FragColor = vec4(light * vertexColor, 1.0);
}
