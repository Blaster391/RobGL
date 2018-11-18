#version 460 core

uniform sampler2D tex;

uniform vec4 lightColour;
uniform vec3 lightDirection;
uniform vec3 lightPosition;
uniform vec3 cameraPos;

uniform int useShadows;

in Vertex	{
	vec4 colour;
	vec3 normals;
	vec2 texCoords;
} IN;


out vec4 fragColour[4];

void main(void)	{	

/*	float shadow = 1.0f;

	vec3 normals = normalize(IN.normals);

	vec3 incident = normalize(lightDirection);
	float lambert = max(0.0, dot(incident, normals));
	
	vec3 viewDir = normalize((cameraPos - IN.worldPos));
	vec3 halfDir = normalize(incident + viewDir);
	
	float rFactor = max(0.0, dot(halfDir,normals));
	float sFactor = pow(rFactor,50);
	
	if(useShadows == 1){
		if(IN.shadowProj.w > 0.0){
			vec3 projCoords = IN.shadowProj.xyz / IN.shadowProj.w;
			projCoords = projCoords * 0.5 + 0.5; 
			float currentDepth = projCoords.z;  
			float closestDepth = texture(shadowTex, projCoords.xy).r;
			float bias = max(0.05 * (1.0 - dot(normals, lightDirection)), 0.005);  
			if(currentDepth - bias > closestDepth){
				shadow = 0.10f;
			}	
		}
	}*/
	
	vec4 texColour =  texture(tex, IN.texCoords);
	
	vec4 combinedColour = texColour * IN.colour;
	
	//Unlit
	fragColour[0] = combinedColour;
	//Normals
	fragColour[1] = vec4(0,0,0,0);
	//Emissive
	fragColour[2] = combinedColour;
	//Specular
	fragColour[3] = vec4(0,0,0,0);
}