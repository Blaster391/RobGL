
#version 460 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

layout(location = 0) in vec3 Position;
layout(location = 2) in vec2 TexCoords;

out mat4 inverseProjView ;

void main(void)	{
	gl_Position		= projMatrix * viewMatrix * modelMatrix * vec4(Position, 1.0);
	inverseProjView = inverse ( projMatrix * viewMatrix );
}