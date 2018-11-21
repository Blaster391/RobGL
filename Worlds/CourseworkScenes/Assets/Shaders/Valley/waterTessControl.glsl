#version 460 core


uniform int inner;
uniform ivec3 outer;

layout(vertices = 3) out;

in Vertex	{
	vec3 worldPos;
	vec2 texCoords;
	vec3 normals;
	vec4 shadowProj;
} IN[];

out Vertex	{
	vec3 worldPos;
	vec2 texCoords;
	vec3 normals;
	vec4 shadowProj;
} OUT[];

void main(void)	{
	gl_TessLevelInner[0] = inner;

	gl_TessLevelOuter [0] = outer[0];
	gl_TessLevelOuter [1] = outer[1];
	gl_TessLevelOuter [2] = outer[2];

	
	gl_out[gl_InvocationID].gl_Position =  gl_in [gl_InvocationID].gl_Position;
	
	OUT[gl_InvocationID].worldPos = IN[gl_InvocationID].worldPos;
	OUT[gl_InvocationID].texCoords = IN[gl_InvocationID].texCoords;
	OUT[gl_InvocationID].normals = IN[gl_InvocationID].normals;
	OUT[gl_InvocationID].shadowProj = IN[gl_InvocationID].shadowProj;

}