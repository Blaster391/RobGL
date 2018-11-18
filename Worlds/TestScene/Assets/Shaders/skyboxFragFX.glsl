#version 460 core

uniform sampler2D tex;
uniform samplerCube skybox;
uniform sampler2D depthTex;
uniform mat4 cameraPos;

in vec3 vsViewDirection;
in vec2 texCoords;

out vec4 fragColour;


void main(void)	{

	float depth = texture(depthTex,texCoords).r;

	if(depth != 1){
		fragColour = texture(tex,texCoords);
	}else{
		//Additive blend for transparent textures that don't write to the depth buffer (i.e particles)
		fragColour = texture(skybox, vsViewDirection) + texture(tex,texCoords);
	}
}