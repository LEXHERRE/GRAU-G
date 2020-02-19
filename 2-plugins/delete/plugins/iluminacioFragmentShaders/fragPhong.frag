#version 330 core

uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 lightPosition;

uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

in vec3 N;
in vec3 P;
out vec4 fragColor;

vec4 Phong(vec3 N, vec3 V, vec3 L) {
  N=normalize(N);
  V=normalize(V);
  L=normalize(L);
  vec3 H=normalize(V+L);
  float NdotL=max(0, dot(N, L));
  float NdotH=max(0, dot(N, H));
  float ldiff=NdotL;
  float lspec=0;
  if (NdotL>0) lspec=pow(NdotH, matShininess);
  return matAmbient*lightAmbient + matDiffuse*lightDiffuse*ldiff + matSpecular*lightSpecular*lspec;
}

void main() {
  vec3 L=lightPosition.xyz-P;
  vec3 V=vec3(0,0,1);
  fragColor=Phong(N, V, L);
}
