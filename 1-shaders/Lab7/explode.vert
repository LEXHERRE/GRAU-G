#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

out vec3 vnormal;
out vec4 vfrontColor;

uniform mat4 modelViewProjectionMatrix;

void main()
{
    vnormal = normal;
    vfrontColor = vec4(color,1.0);
    gl_Position = vec4(vertex, 1.0);
}
