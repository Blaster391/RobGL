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
		fragColour = texture(skybox, vsViewDirection);
	}

	//fragColour = vec4(1,0,0,1);
}