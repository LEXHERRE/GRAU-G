#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec3 V;

void main()
{
    vec3 normal = normalize(cross(dFdx(V),dFdy(V)));
    fragColor = frontColor * normal.z;
}
