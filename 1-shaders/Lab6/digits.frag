#version 330 core

uniform sampler2D colorMap;
uniform float time;

in vec2 vtexCoord;
out vec4 fragColor;

void main()
{
    float c = time/100;
    float d = (mod(time,100))/10;
    float u = mod(time,10);


    vec2 ftexCoord = vtexCoord;

    if (vtexCoord.x < 0.1) 
    {
        ftexCoord.x = vtexCoord.x + int(c)/10.0;
    }
    else if (vtexCoord.x >= 0.1 && vtexCoord.x < 0.2) 
    {
        ftexCoord.x = vtexCoord.x + int(d)/10.0 - 0.1;
    }
    else
    {
        ftexCoord.x = vtexCoord.x + int(u)/10.0 - 0.2;
    }
    fragColor = texture(colorMap, ftexCoord);
    if (fragColor.a < 0.5) discard;
    else fragColor = vec4(1,0,0,1);
} 
