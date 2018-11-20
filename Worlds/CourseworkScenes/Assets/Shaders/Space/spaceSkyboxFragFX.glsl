#version 460 core

uniform sampler2D tex;

uniform samplerCube skybox;
uniform samplerCube skybox2;
uniform samplerCube skybox3;

uniform float tweenTime;
uniform float currentTime;

uniform sampler2D depthTex;
uniform mat4 cameraPos;

in vec3 vsViewDirection;
in vec2 texCoords;

out vec4 fragColour;


void main(void)	{

	vec4 colour = texture(tex,texCoords);

	float skybox1Amount = 1;
	float skybox2Amount = 1;
	float skybox3Amount = 1;

	float thirdTweenTime = tweenTime / 3;
	
	if(currentTime < thirdTweenTime){
		skybox3Amount = 0;
		skybox1Amount = 1 - (currentTime / thirdTweenTime);
		skybox2Amount = (currentTime / thirdTweenTime);
	}else if(currentTime < thirdTweenTime * 2){
		skybox1Amount = 0;
		float modTime = currentTime - thirdTweenTime;
		skybox2Amount = 1 - (modTime / thirdTweenTime);
		skybox3Amount = (modTime / thirdTweenTime);
	}else{
		skybox2Amount = 0;
		float modTime = currentTime - thirdTweenTime * 2;
		skybox3Amount = 1 - (modTime / thirdTweenTime);
		skybox1Amount = (modTime / thirdTweenTime);
		
	}

	fragColour = ((texture(skybox, vsViewDirection) * skybox1Amount) + (texture(skybox2, vsViewDirection) * skybox2Amount) + (texture(skybox3, vsViewDirection) * skybox3Amount)) * (1 - colour.a) + (colour * colour.a);

}