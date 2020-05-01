#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 fragPos_view;
out vec3 vertexColor;
out vec3 vertexNormal_view;


void main()
{
    fragPos_view        = vec3(view * model * vec4(pos, 1.0));
    vertexColor         = vec3(1.0, 0.0, 0.0);
    vertexNormal_view   = vec3(view * model * vec4(normal, 1.0));
    gl_Position         = projection * vec4(fragPos_view, 1.0);
}

