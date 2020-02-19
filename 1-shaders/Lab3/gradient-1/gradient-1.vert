#version 330 core

layout (location = 0) in vec3 vertex;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;

uniform vec3 boundingBoxMax;
uniform vec3 boundingBoxMin;

vec4 vermell = vec4(1,0,0,1);
vec4 groc = vec4(1,1,0,1);
vec4 verd = vec4(0,1,0,1);
vec4 cian = vec4(0,1,1,1);
vec4 blau = vec4(0,0,1,1);

void main()
{
    float top = boundingBoxMax.y;
    float bot = boundingBoxMin.y;
    float pos = 4*(vertex.y-bot)/(top-bot);
   
    if (pos==0) frontColor = vermell;
    else if (pos<1) frontColor = mix(vermell,groc,fract(pos));
    else if (pos<2) frontColor = mix(groc,verd,fract(pos));
    else if (pos<3) frontColor = mix(verd,cian,fract(pos));
    else if (pos<4) frontColor = mix(cian,blau,fract(pos));
    else frontColor = blau;
    
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
