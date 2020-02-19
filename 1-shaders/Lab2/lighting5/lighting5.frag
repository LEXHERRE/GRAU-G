#version 330 core

out vec4 fragColor;

in vec3 NEye;
in vec3 VEye;
in vec3 LEye;

in vec3 NWorld;
in vec3 VWorld;
in vec3 LWorld;

uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;

uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

uniform bool world = true;

vec4 Phong(vec3 N, vec3 V, vec3 L) {
    N=normalize(N);
    V=normalize(V);
    L=normalize(L);
    vec3 R = normalize( 2.0*dot(N,L)*N-L );
    float NdotL = max( 0.0, dot( N,L ) );
    float RdotV = max( 0.0, dot( R,V ) );
    float Idiff = NdotL;
    float Ispec = 0;
    if (NdotL>0) Ispec=pow( RdotV, matShininess );
    return matAmbient * lightAmbient + matDiffuse * lightDiffuse * Idiff + matSpecular * lightSpecular * Ispec;
}

void main()
{
    if (world) fragColor = Phong(NWorld,LWorld,VWorld);
    else fragColor = Phong(NEye,LEye,VEye);
}
