#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 2) in vec3 color;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;

uniform float time;

void main()
{
    frontColor = vec4(color,1.0);
    float theta = 0.4* vertex.y * sin(time);
    mat3 rot = mat3(vec3(cos(theta),0,sin(theta)),vec3(0,1,0),vec3(-sin(theta),0,cos(theta)));
    gl_Position = modelViewProjectionMatrix * vec4(vertex*rot, 1.0);
}
