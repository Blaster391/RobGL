#version 460 core

uniform sampler2D shadowTex;

uniform vec4 lightColour;
uniform vec3 lightDirection;
uniform vec3 lightPosition;
uniform vec3 cameraPos;

uniform int useShadows;

in Vertex	{
	vec3 worldPos;
	vec4 colour;
	vec3 normals;
	vec4 shadowProj;
} IN;

out vec4 fragColour[4];

void main(void)	{	

	float shadow = 1.0f;

	vec3 normals = normalize(IN.normals);

	vec3 incident = normalize(lightDirection);
	float lambert = max(0.0, dot(incident, normals));
	
	vec3 viewDir = normalize((cameraPos - IN.worldPos));
	vec3 halfDir = normalize(incident + viewDir);
	
	float rFactor = max(0.0, dot(halfDir,normals));
	float sFactor = pow(rFactor,50);
	
	if(useShadows == 1){
		if(IN.shadowProj.w > 0.0){
		//	shadow = textureProj(shadowTex, IN.shadowProj);
		}
	}
	
	//Unlit
	fragColour[0] = IN.colour;
	//Normals
	fragColour[1] = vec4(normals,1);
	//Emissive
	fragColour[2] = vec4(lightColour.rgb * lambert * shadow, 1);
	//Specular
	fragColour[3] = vec4(((lightColour.rgb * sFactor) * 0.33f * shadow),1);
}