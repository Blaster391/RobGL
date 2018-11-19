#version 460 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

layout(location = 0) in vec3 Position;

void main(void)	{
	gl_Position =  projMatrix * viewMatrix * modelMatrix * vec4(Position, 1.0);
}