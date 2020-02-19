#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 2) in vec3 color;

out vec4 frontColor;
uniform mat4 modelViewProjectionMatrix;

uniform float time;

void main()
{
    frontColor = vec4(color,1.0);
    float theta = (vertex.y-0.5)*sin(time);
    mat3 rot = mat3(vec3(1,0,0),vec3(0,cos(theta),sin(theta)),vec3(0,-sin(theta),cos(theta)));
    vec3 v = vertex + vec3(0,-1,0);
    if (vertex.y > 0.5) {v = rot*v;}
    v += vec3(0,1,0);
    gl_Position = modelViewProjectionMatrix * vec4(v, 1.0);
}
