#version 460 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

layout(location = 0) in vec3 Position;
layout(location = 2) in vec2 TexCoords;

out Vertex	{
	vec2 texCoords;
} OUT;

void main(void)	{
	gl_Position		= projMatrix * vec4(Position, 1.0);
	OUT.texCoords		= TexCoords;
}