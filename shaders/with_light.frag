#version 330 core

in vec3  fragPos_view;
in vec3  vertexColor;
in vec3  vertexNormal_view;

uniform mat4 model; 
uniform mat4 view;
uniform vec3 lightColor;
uniform vec3 lightPos_world;
uniform vec3 viewPos_world;

out vec4 FragColor;

void main()
{
    // Vectors in 'view' co-ordinates
    vec3 viewPos_view     = vec3(view * vec4(viewPos_world, 1.0));
    vec3 lightPos_view    = vec3(view * vec4(lightPos_world, 1.0));
    vec3 lightDir_view    = normalize(lightPos_view - fragPos_view);
    vec3 viewDir_view     = normalize(viewPos_view - fragPos_view);
    vec3 reflectDir_view  = reflect(-lightDir_view, normalize(vertexNormal_view));

    // Ambient
    float ambientStrength = 0.2;

    // Diffuse
    float diffuseFactor  = 0.3;
    float diffuseStrength = diffuseFactor * max(dot(lightDir_view, normalize(vertexNormal_view)), 0.0);

    // Specular
    float specularFactor = 0.3;
    float spec = pow( max( dot(viewDir_view, reflectDir_view), 0.0), 64);
    float specularStrength = specularFactor * spec;

    //vec3 light = diffuseStrength  * lightColor;
    //vec3 light = specularStrength * lightColor;
    vec3 light = (ambientStrength + diffuseStrength + specularStrength) * lightColor;
    FragColor = vec4(light * vertexColor, 1.0);
}
