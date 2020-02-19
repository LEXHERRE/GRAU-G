#version 330 core

out vec4 fragColor;

uniform sampler2D noise0;
uniform sampler2D rock1;
uniform sampler2D grass2;

in vec2 vtexCoord;

void main()
{
    float soroll = texture(noise0,vtexCoord).r;
    vec4 roca = texture(rock1,vtexCoord);
    vec4 gespa =texture(grass2,vtexCoord);
    fragColor =  mix(roca, gespa, soroll);
}
