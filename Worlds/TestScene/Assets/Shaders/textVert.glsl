#version 460 core

layout(location = 0) in vec3 Position;
layout(location = 2) in vec2 TexCoords;

out Vertex	{
	vec2 texCoords;
} OUT;

void main(void)	{
	gl_Position		= vec4(Position, 1.0);
	OUT.texCoords	= TexCoords;
}