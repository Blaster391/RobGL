#version 460 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

layout(location = 0) in vec3 Position;
layout(location = 2) in vec2 TexCoords;
layout(location = 3) in vec3 Normals;

out Vertex	{
	vec2 texCoords;
	vec3 normals;
} OUT;

void main(void)	{
	gl_Position		= projMatrix * viewMatrix * modelMatrix * vec4(Position, 1.0);

	OUT.texCoords		= TexCoords;
	OUT.normals = Normals;
}