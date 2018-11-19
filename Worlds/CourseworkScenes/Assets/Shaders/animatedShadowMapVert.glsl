#version 460 core

uniform mat4[50] jointMatrices;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

layout(location = 0) in vec3 Position;

layout(location = 4) in vec4 Joints;
layout(location = 5) in vec4 Weights;

void main(void)	{
	vec4 j = Joints;
	
	mat4 skinMatrix = 
				Weights.x * jointMatrices[int(j.x)] +
				Weights.y * jointMatrices[int(j.y)] +
				Weights.z * jointMatrices[int(j.z)] +
				Weights.w * jointMatrices[int(j.w)];
	
	gl_Position		= projMatrix * viewMatrix * modelMatrix * skinMatrix * vec4(Position, 1.0);
}