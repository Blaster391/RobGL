#version 460 core

uniform mat4[50] jointMatrices;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

uniform mat4 shadowMatrix;


layout(location = 0) in vec3 Position;
layout(location = 2) in vec2 TexCoords;
layout(location = 3) in vec3 Normals;

layout(location = 4) in vec4 Joints;
layout(location = 5) in vec4 Weights;

out Vertex	{
	vec3 worldPos;
	vec2 texCoords;
	vec3 normals;
	vec4 shadowProj;
} OUT;

void main(void)	{
	vec4 j = Joints;
	
	mat4 skinMatrix = 
				Weights.x * jointMatrices[int(j.x)] +
				Weights.y * jointMatrices[int(j.y)] +
				Weights.z * jointMatrices[int(j.z)] +
				Weights.w * jointMatrices[int(j.w)];
	
	gl_Position		= projMatrix * viewMatrix * modelMatrix * skinMatrix * vec4(Position, 1.0);

	OUT.worldPos    =  (modelMatrix * vec4(Position,1)).xyz;
	OUT.texCoords = TexCoords;
	
	mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
	
	OUT.normals = normalize(normalMatrix * Normals);
	OUT.shadowProj = (shadowMatrix * (modelMatrix * vec4(Position,1)));
}