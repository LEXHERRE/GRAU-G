#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 2) in vec3 color;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;

const float radi = 1;

void main()
{
    frontColor = vec4(color,1.0);
    vec3 v = normalize(vertex)*radi;
    gl_Position = modelViewProjectionMatrix * vec4(v, 1.0);
} 
