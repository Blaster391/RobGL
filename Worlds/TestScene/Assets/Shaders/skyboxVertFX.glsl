#version 460 core



 
uniform mat4 inverseViewMatrix;
uniform mat4 inverseProjectionMatrix;
 
layout(location = 0) in vec3 Position;
 
layout(location = 2) in vec2 TexCoords;

 
out vec3 vsViewDirection;
 out vec2 texCoords;
 
void main()
{
    gl_Position		= vec4(Position, 1.0);
    vsViewDirection = mat3(inverseViewMatrix) * (inverseProjectionMatrix * gl_Position).xyz;
	texCoords = TexCoords;
}