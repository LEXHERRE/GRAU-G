#version 330 core

out vec4 fragColor;
in vec2 vtexCoord;

vec4 BLACK = vec4(0,0,0,1);
vec4 GREY = vec4(0.8);

uniform float n = 8;
const float thickness = 0.1;

void main()
{
    float x = fract(vtexCoord.x*n);
    float y = fract(vtexCoord.y*n);
    
    if (x>thickness && y>thickness) fragColor = GREY;
    else fragColor = BLACK;
}
