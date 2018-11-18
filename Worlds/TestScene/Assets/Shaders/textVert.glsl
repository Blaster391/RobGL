#version 460 core

uniform mat4 modelMatrix;

layout(location = 0) in vec3 Position;
layout(location = 2) in vec2 TexCoords;

out Vertex	{
	vec2 texCoords;
} OUT;

void main(void)	{
	vec2 correctedTexCoords = TexCoords;


	gl_Position		= modelMatrix * vec4(Position, 1.0);
	OUT.texCoords	= vec2(TexCoords.x,1-TexCoords.y);
}