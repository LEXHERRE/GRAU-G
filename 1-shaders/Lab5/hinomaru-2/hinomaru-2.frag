#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

const vec2 centre = vec2(0.5);
const int nRaigs = 16;
const float PI=3.14159265;
const float fi = PI/nRaigs;

uniform bool classic = false;

float aastep(float threshold, float x)
{
    float width = 0.7*length(vec2(dFdx(x), dFdy(x)));
    return smoothstep(threshold-width, threshold+width, x);
}

void main()
{
    float d = length(vec2(vtexCoord.x-centre.x, vtexCoord.y-centre.y));
    fragColor=vec4(1.0, vec2(aastep(0.2, d)), 1.0);
    if (!classic) {
        vec2 u = vec2(vtexCoord.t-centre.x, vtexCoord.s-centre.y);
        float theta = atan(u.s,u.t);
        if (mod(theta/fi + 0.5, 2) < 1) fragColor=vec4(1.0, 0, 0, 1.0);
    }
}
