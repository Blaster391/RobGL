#version 460 core

uniform sampler2D tex;
uniform sampler2D shadowTex;

uniform vec4 lightColour;
uniform vec3 lightDirection;
uniform vec3 lightPosition;
uniform vec3 cameraPos;

uniform int useShadows;


uniform mat4 shadowMatrix;

in Vertex	{
	vec3 worldPos;
	vec2 texCoords;
	vec3 normals;
	vec4 shadowProj;
} IN;

out vec4 fragColour[4];

void main(void)	{

	float shadow = 1.0f;

	vec3 normals = normalize(IN.normals);

	vec3 incident = normalize(lightDirection);
	float lambert = max(0.0, dot(incident, normals));
	
	vec3 viewDir = normalize((IN.worldPos- cameraPos));
	vec3 halfDir = normalize(incident + viewDir);
	
	float rFactor = max(0.0, dot(halfDir,normals));
	float sFactor = pow(rFactor,50);

	if(useShadows == 1){
		if(IN.shadowProj.w > 0.0){
			vec3 projCoords = IN.shadowProj.xyz / IN.shadowProj.w;
			projCoords = projCoords * 0.5 + 0.5; 
			float currentDepth = projCoords.z;  
			float closestDepth = texture(shadowTex, projCoords.xy).r;
			float bias = max(0.01 * (1.0 - dot(normals, lightDirection)), 0.005);  
			bias = 0.000f;
			if(currentDepth - bias > closestDepth){
				shadow = 0.10f;
			}
		}
	}
	
	//Unlit
	fragColour[0] = texture(tex,IN.texCoords);
	
	//Normals
	fragColour[1] = vec4(normals,1);
	//Emissive
	fragColour[2] = vec4(lightColour.rgb * lambert * shadow, 1);
	//Specular
	fragColour[3] = vec4(((lightColour.rgb * sFactor) * 0.01f * shadow),1);

	
	//FOR DEBUGGING
	//fragColour[3] = vec4(debug.x,debug.y,debug.z,1);
}