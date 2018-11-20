#version 460 core

uniform sampler2D tex;
uniform samplerCube skybox;
uniform sampler2D depthTex;
uniform mat4 cameraPos;

in vec3 vsViewDirection;
in vec2 texCoords;

out vec4 fragColour;


void main(void)	{

	vec4 colour = texture(tex,texCoords);

	fragColour = texture(skybox, vsViewDirection) * (1 - colour.a) + (colour * colour.a);
	
}