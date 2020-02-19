#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float step=0.175;

out vec4 gfrontColor;

const vec4 GREY=vec4(vec3(0.8), 1);

void main( void )
{
    vec3 c = (gl_in[0].gl_Position.xyz+gl_in[1].gl_Position.xyz+gl_in[2].gl_Position.xyz)/3;
    c /= step;
    c.x = int(c.x);
    c.y = int(c.y);
    c.z = int(c.z);
    c *= step;
    
    float R = step/2;
    
    
    vec3 N=normalMatrix*vec3(1, 0, 0);
    vec4 color = GREY*N.z;
    
    gfrontColor = color;
	gl_Position = modelViewProjectionMatrix*vec4(c+vec3( R, R, R),1);
	EmitVertex();
    
    gfrontColor = color;
	gl_Position = modelViewProjectionMatrix*vec4(c+vec3( R, R,-R),1);
	EmitVertex();
    
    gfrontColor = color;
	gl_Position = modelViewProjectionMatrix*vec4(c+vec3( R,-R, R),1);
	EmitVertex();
    
    gfrontColor = color;
	gl_Position = modelViewProjectionMatrix*vec4(c+vec3( R,-R,-R),1);
	EmitVertex();
	
	EndPrimitive();
	
	
	N=normalMatrix*vec3(-1, 0, 0);
    color = GREY*N.z;
	
    gfrontColor = color;
	gl_Position = modelViewProjectionMatrix*vec4(c+vec3(-R, R, R),1);
	EmitVertex();
    
    gfrontColor = color;
	gl_Position = modelViewProjectionMatrix*vec4(c+vec3(-R, R,-R),1);
	EmitVertex();
    
    gfrontColor = color;
	gl_Position = modelViewProjectionMatrix*vec4(c+vec3(-R,-R, R),1);
	EmitVertex();
    
    gfrontColor = color;
	gl_Position = modelViewProjectionMatrix*vec4(c+vec3(-R,-R,-R),1);
	EmitVertex();
	
	EndPrimitive();
	
	
	N=normalMatrix*vec3(0, 1, 0);
    color = GREY*N.z;
    
    gfrontColor = color;
	gl_Position = modelViewProjectionMatrix*vec4(c+vec3( R, R, R),1);
	EmitVertex();
    
    gfrontColor = color;
	gl_Position = modelViewProjectionMatrix*vec4(c+vec3( R, R,-R),1);
	EmitVertex();
    
    gfrontColor = color;
	gl_Position = modelViewProjectionMatrix*vec4(c+vec3(-R, R, R),1);
	EmitVertex();
    
    gfrontColor = color;
	gl_Position = modelViewProjectionMatrix*vec4(c+vec3(-R, R,-R),1);
	EmitVertex();
	
	EndPrimitive();
	
	
	N=normalMatrix*vec3(0, -1, 0);
    color = GREY*N.z;
    
    gfrontColor = color;
	gl_Position = modelViewProjectionMatrix*vec4(c+vec3( R,-R, R),1);
	EmitVertex();
    
    gfrontColor = color;
	gl_Position = modelViewProjectionMatrix*vec4(c+vec3( R,-R,-R),1);
	EmitVertex();
    
    gfrontColor = color;
	gl_Position = modelViewProjectionMatrix*vec4(c+vec3(-R,-R, R),1);
	EmitVertex();
    
    gfrontColor = color;
	gl_Position = modelViewProjectionMatrix*vec4(c+vec3(-R,-R,-R),1);
	EmitVertex();
	
	EndPrimitive();
	
	
	N=normalMatrix*vec3(0, 0, 1);
    color = GREY*N.z;
    
    gfrontColor = color;
	gl_Position = modelViewProjectionMatrix*vec4(c+vec3( R, R, R),1);
	EmitVertex();
    
    gfrontColor = color;
	gl_Position = modelViewProjectionMatrix*vec4(c+vec3( R,-R, R),1);
	EmitVertex();
    
    gfrontColor = color;
	gl_Position = modelViewProjectionMatrix*vec4(c+vec3(-R, R, R),1);
	EmitVertex();
    
    gfrontColor = color;
	gl_Position = modelViewProjectionMatrix*vec4(c+vec3(-R,-R, R),1);
	EmitVertex();
	
	EndPrimitive();
	
	
	N=normalMatrix*vec3(0, 0, 1);
    color = GREY*N.z;
    
    gfrontColor = color;
	gl_Position = modelViewProjectionMatrix*vec4(c+vec3( R, R,-R),1);
	EmitVertex();
    
    gfrontColor = color;
	gl_Position = modelViewProjectionMatrix*vec4(c+vec3( R,-R,-R),1);
	EmitVertex();
    
    gfrontColor = color;
	gl_Position = modelViewProjectionMatrix*vec4(c+vec3(-R, R,-R),1);
	EmitVertex();
    
    gfrontColor = color;
	gl_Position = modelViewProjectionMatrix*vec4(c+vec3(-R,-R,-R),1);
	EmitVertex();
	
	EndPrimitive();
}
