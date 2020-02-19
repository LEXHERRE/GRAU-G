#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 3) in vec2 texCoord;

out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;

uniform int tiles=2;

void main()
{
    vtexCoord = texCoord*tiles;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
