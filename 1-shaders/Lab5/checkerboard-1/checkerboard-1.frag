#version 330 core

out vec4 fragColor;
in vec2 vtexCoord;

vec4 BLACK = vec4(0,0,0,1);
vec4 GREY = vec4(0.8);

void main()
{
    float x = int(mod((vtexCoord.x*8),2));
    float y = int(mod((vtexCoord.y*8),2));
    
    if (x == y) fragColor = GREY;
    else fragColor = BLACK;
}
