#version 460 core

uniform samplerCube skybox;
uniform mat4 cameraPos;

in vec3 vsViewDirection;
out vec4 fragColour;


void main(void)	{
	fragColour = texture(skybox, vsViewDirection);
	
	//fragColour = vec4(1,0,0,1);
}