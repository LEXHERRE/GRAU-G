#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

uniform mat4 modelViewProjectionMatrix;
uniform float time;

in vec3 vnormal[];
in vec4 vfrontColor[];
out vec4 gfrontColor;

const float speed = 0.5;

void main( void )
{
    vec3 N = speed*time*(vnormal[0]+vnormal[1]+vnormal[2])/3;
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		vec3 V = gl_in[i].gl_Position.xyz+N;
		gl_Position = modelViewProjectionMatrix*vec4(V,1);
		EmitVertex();
	}
    EndPrimitive();
}
