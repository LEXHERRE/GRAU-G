#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

out vec3 fvertex;
out vec3 fnormal;

uniform mat4 modelViewProjectionMatrix;

void main()
{
    fvertex = vertex;
    fnormal = normal;

    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
