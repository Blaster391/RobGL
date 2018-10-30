#version 460 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

layout(location = 0) in vec3 Position;
layout(location = 1) in vec4 Colour;

out Vertex	{
	vec4 colour;
} OUT;

mat4 m = mat4(vec4(100, 0, 0, 0),
		  vec4(0, 100, 0, 0),
		  vec4(0, 0, 100, 1000),
		  vec4(0, 0, 0, 1));

void main(void)	{
	gl_Position		= projMatrix * viewMatrix * modelMatrix vec4(Position, 1.0);
	OUT.colour		= Colour;
}