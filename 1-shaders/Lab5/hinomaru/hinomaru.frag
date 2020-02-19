#version 330 core

in vec2 vtexCoord;
out vec4 fragColor;

const vec2 centre = vec2(0.5);

float aastep(float threshold, float x)
{
    float width = 0.7*length(vec2(dFdx(x), dFdy(x)));
    return smoothstep(threshold-width, threshold+width, x);
}

void main()
{
    float d = length(vec2(vtexCoord.x-centre.x, vtexCoord.y-centre.y));
    fragColor=vec4(1.0, vec2(step(0.2, d)), 1.0);
}
