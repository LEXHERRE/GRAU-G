#version 330 core

out vec4 fragColor;
in vec2 vtexCoord;
in vec3 N;

uniform sampler2D colormap;

const float radi = 0.05;

float aastep(float threshold, float x)
{
    float width = 0.7*length(vec2(dFdx(x), dFdy(x)));
    return smoothstep(threshold-width, threshold+width, x);
}

void main()
{
    vec2 C1 = vec2(0.34,0.65)-0.1*N.xy;
    vec2 C2 = vec2(0.66,0.65)-0.1*N.xy;
    
    float d1 = length(vec2(vtexCoord.x-C1.x, vtexCoord.y-C2.y));
    float d2 = length(vec2(vtexCoord.x-C2.x, vtexCoord.y-C2.y));
    fragColor = texture(colormap, vtexCoord);
    if (step(d1, radi)>0 || step(d2, radi)>0) fragColor=vec4(0);
}
