#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewProjectionMatrixInverse;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

in vec4 vfrontColor[];
out vec4 gfrontColor;

const vec4 BLACK = vec4(0,0,0,1);
const vec4 CIAN = vec4(0,1,1,1);
const float delta = 0.01;

void main( void )
{ 
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
    
    for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = BLACK;
		vec4 V = modelViewProjectionMatrixInverse*gl_in[i].gl_Position;
		V.y = boundingBoxMin.y;
		gl_Position = modelViewProjectionMatrix*V;
		EmitVertex();
	}
    EndPrimitive();
    
    if (gl_PrimitiveIDIn == 0){
        float R = length(boundingBoxMax-boundingBoxMin)/2;
        vec3 C = (boundingBoxMax+boundingBoxMin)/2;
        float y = boundingBoxMin.y-delta;
        
        gfrontColor = CIAN;
        gl_Position = modelViewProjectionMatrix*vec4(C.x+R, y, C.z+R,1);
        EmitVertex();
        
        gfrontColor = CIAN;
        gl_Position = modelViewProjectionMatrix*vec4(C.x+R, y, C.z-R,1);
        EmitVertex();
        
        gfrontColor = CIAN;
        gl_Position = modelViewProjectionMatrix*vec4(C.x-R, y, C.z+R,1);
        EmitVertex();
        
        gfrontColor = CIAN;
        gl_Position = modelViewProjectionMatrix*vec4(C.x-R, y, C.z-R,1);
        EmitVertex();
        
        EndPrimitive();
    }
}
