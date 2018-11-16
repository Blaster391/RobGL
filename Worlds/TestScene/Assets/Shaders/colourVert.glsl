#version 460 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

layout(location = 0) in vec3 Position;
layout(location = 1) in vec4 Colour;
layout(location = 3) in vec3 Normals;

out Vertex	{
	vec3 worldPos;
	vec4 colour;
	vec3 normals;
} OUT;

void main(void)	{
	gl_Position		= projMatrix * viewMatrix * modelMatrix * vec4(Position, 1.0);
	OUT.worldPos    =  (modelMatrix * vec4(Position,1)).xyz;
	OUT.colour		= Colour;
	OUT.normals 	= Normals;
}