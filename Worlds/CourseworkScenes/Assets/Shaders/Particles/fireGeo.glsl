#version 460 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

uniform float particleSize;

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in Vertex{
	vec4 colour;
	vec3 normals;
} IN[];

out Vertex	{
	vec4 colour;
	vec3 normals;
	vec2 texCoords;
} OUT;

void main(void)	{


	gl_Position = gl_in[0].gl_Position + vec4(particleSize,particleSize,0,1);
	OUT.colour = IN[0].colour;
	OUT.normals = IN[0].normals;
	OUT.texCoords = vec2(1,1);
	EmitVertex();
	
	gl_Position = gl_in[0].gl_Position + vec4(-particleSize,particleSize,0,1);
	OUT.colour = IN[0].colour;
	OUT.normals = IN[0].normals;
	OUT.texCoords = vec2(0,1);
	EmitVertex();

	
	gl_Position = gl_in[0].gl_Position + vec4(particleSize,-particleSize,0,1);
	OUT.colour = IN[0].colour;
	OUT.normals = IN[0].normals;
	OUT.texCoords = vec2(1,0);
	EmitVertex();
	
	gl_Position = gl_in[0].gl_Position + vec4(-particleSize,-particleSize,0,1);
	OUT.colour = IN[0].colour;
	OUT.normals = IN[0].normals;
	OUT.texCoords = vec2(0,0);
	EmitVertex();
	
	
	EndPrimitive();
	
	
}