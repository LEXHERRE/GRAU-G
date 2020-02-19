#version 330 core

in vec3 fvertex;
in vec3 fnormal;
out vec4 fragColor;

uniform int n = 4;
const float pi = 3.141592;

uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

uniform vec4 matAmbient, matDiffuse, matSpecular;
uniform float matShininess;
uniform vec4 lightAmbient, lightDiffuse, lightSpecular, lightPosition;

vec4 light(vec3 N, vec3 V, vec3 L) 
{
    N = normalize(N);
    V = normalize(V);
    L = normalize(L);
    vec3 R = normalize(2.0*dot(N,L)*N-L);
    float NdotL = max(0.0, dot(N,L));
    float RdotV = max(0.0, dot(R,V));
    float Idiff = NdotL;
    float Ispec = 0;
    if(NdotL > 0) Ispec = pow(RdotV, matShininess);
    return matDiffuse*lightDiffuse*Idiff/sqrt(float(n)) + matSpecular*lightSpecular*Ispec;
}

void main()
{
    vec3 P = (modelViewMatrix*vec4(fvertex.xyz,1.0)).xyz;
    vec3 N = normalMatrix*fnormal;
    vec3 V = -P;
    vec3 L_ini = vec3(10,0,0)-P;
    fragColor = vec4(0);
    for (int i = 0; i < n; ++i) {
        float angle = ((2*pi)/n)*i;
        mat3 rotacioAngleZ= mat3(vec3(cos(angle), -sin(angle),0), vec3(sin(angle), cos(angle), 0),
        vec3(0, 0, 1));
        vec3 L = L_ini*rotacioAngleZ;
        fragColor += light(N,V,L);
    }
}
