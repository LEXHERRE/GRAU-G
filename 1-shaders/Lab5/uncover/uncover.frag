#version 330 core

out vec4 fragColor;
in float pos;

uniform float time;

void main()
{
    if (pos<=time) fragColor = vec4(0,0,1,1);
    else discard;
}
