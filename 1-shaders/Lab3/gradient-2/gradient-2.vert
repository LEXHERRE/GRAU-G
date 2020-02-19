#version 330 core

layout (location = 0) in vec3 vertex;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;

vec4 vermell = vec4(1,0,0,1);
vec4 groc = vec4(1,1,0,1);
vec4 verd = vec4(0,1,0,1);
vec4 cian = vec4(0,1,1,1);
vec4 blau = vec4(0,0,1,1);

void main()
{
    gl_Position =modelViewProjectionMatrix * vec4(vertex, 1.0);
   
   float posY = 2*(gl_Position.y/gl_Position.w+1.0);

    if (posY<0) frontColor = vermell;
    else if (posY<1) frontColor = mix(vermell,groc,fract(posY));
    else if (posY<2) frontColor = mix(groc,verd,fract(posY));
    else if (posY<3) frontColor = mix(verd,cian,fract(posY));
    else if (posY<4) frontColor = mix(cian,blau,fract(posY));
    else frontColor = blau;
}
