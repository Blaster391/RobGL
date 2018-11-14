#version 460 core



 
uniform mat4 inverseViewMatrix;
uniform mat4 inverseProjectionMatrix;
 
layout(location = 0) in vec3 Position;
 
out vec3 vsViewDirection;
 
void main()
{
    gl_Position		= vec4(Position, 1.0);
    vsViewDirection = mat3(inverseViewMatrix) * (inverseProjectionMatrix * gl_Position).xyz;
}