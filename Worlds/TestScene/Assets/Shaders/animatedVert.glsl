#version 460 core

uniform mat4[50] jointMatrices;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

layout(location = 0) in vec3 Position;
layout(location = 2) in vec2 TexCoords;

layout(location = 4) in uvec4 Joints;
layout(location = 5) in vec4 Weights;

out Vertex	{
	vec2 texCoords;
} OUT;

void main(void)	{
	uvec4 j = Joints;

	if(j.x == 0 || j.x > 5){
		j.x  = 4;
	}
	if(j.y == 0 || j.y > 5){
		j.y  = 4;
	}
	if(j.z == 0 || j.z > 5){
		j.z  = 4;
	}
	if(j.w == 0 || j.w > 5){
		j.w  = 4;
	}
	
	mat4 skinMatrix = 
				Weights.x * jointMatrices[j.x] +
				Weights.y * jointMatrices[j.y] +
				Weights.z * jointMatrices[j.z] +
				Weights.w * jointMatrices[j.w];
	
/*	
	mat4 skinMatrix = 
				Weights.x * jointMatrices[Joints.x] +
				Weights.y * jointMatrices[Joints.y] +
				Weights.z * jointMatrices[Joints.z] +
				Weights.w * jointMatrices[Joints.w];
*/
	gl_Position		= projMatrix * viewMatrix * modelMatrix * skinMatrix * vec4(Position, 1.0);

	OUT.texCoords		= TexCoords;
}