#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
in vec3 vNormal[];
out vec3 gNormal;
uniform mat4 modelViewProjectionMatrix;
uniform float disp= 0.06;

vec3 getNormal(vec3 A, vec3 B, vec3 C) {
  vec3 P=B-A;
  vec3 Q=C-A;
  return vec3(P.y*Q.z-P.z*Q.y,P.z*Q.x-P.x*Q.z,P.x*Q.y-P.y*Q.x);
}

void pinta(vec3 V, int i){
	gl_Position = modelViewProjectionMatrix*vec4(V,1);
	if( i == 3){
		gNormal =normalize(getNormal(vNormal[0],vNormal[1],vNormal[2]));
		gfrontColor = vec4 (1,1,1,1);
	}
	else{
		gNormal=normalize(vNormal[i]);
		gfrontColor= vfrontColor[i];
	}
	EmitVertex();
}

void piramide(vec3 V1, vec3 V2, vec3 V3, vec3 BC){
	BC = BC + normalize(vNormal[0])*disp;
	//costat1
	pinta(V1,0);
	pinta(V2,1);
	pinta(BC,3);
	EndPrimitive();
	//costat2
	pinta(V1,0);
	pinta(V3,2);
	pinta(BC,3);
	EndPrimitive();
	//costat3
	pinta(V2,1);
	pinta(V3,2);
	pinta(BC,3);
	EndPrimitive();
}

void main( void )
{
	vec3 BT=(gl_in[0].gl_Position.xyz+
          gl_in[1].gl_Position.xyz+
          gl_in[2].gl_Position.xyz)/3;
    piramide(gl_in[0].gl_Position.xyz, gl_in[1].gl_Position.xyz, gl_in[2].gl_Position.xyz, BT);     
}
