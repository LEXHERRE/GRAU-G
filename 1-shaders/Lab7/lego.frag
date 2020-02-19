#version 330 core

in float gtop;
in vec3 gnormal;
in vec2 gtexCoord;
in vec4 gfrontColor;
out vec4 fragColor;

uniform sampler2D lego;

const vec4 R = vec4(1,0,0,1);
const vec4 G =vec4(0,1,0,1);
const vec4 B =vec4(0,0,1,1);
const vec4 C =vec4(0,1,1,1);
const vec4 Y =vec4(1,1,0,1);

vec4 closestColor(vec4 col){
    float distR = length(col-R);
    float distG = length(col-G);
    float distB = length(col-B);
    float distC = length(col-C);
    float distY = length(col-Y);
    
    if (distR<=distG && distR<=distB && distR<=distC && distR<=distY) return R;
    if (distG<=distR && distG<=distB && distG<=distC && distG<=distY) return G;
    if (distB<=distG && distB<=distR && distB<=distC && distB<=distY) return B;
    if (distC<=distG && distC<=distB && distC<=distR && distC<=distY) return C;
    return Y;
}

void main()
{
    fragColor = closestColor(gfrontColor)*normalize(gnormal).z;
    if (gtop>0) fragColor*=texture2D(lego,gtexCoord);
}
