#version 460 core

uniform sampler2D tex;

uniform vec4 lightColour;
uniform vec3 lightDirection;
uniform vec3 lightPosition;
uniform vec3 cameraPos;

in Vertex	{
	vec3 worldPos;
	vec2 texCoords;
	vec3 normals;
} IN;

out vec4 fragColour[4];

void main(void)	{

	vec3 normals = normalize(IN.normals);

	vec3 incident = normalize(lightDirection);
	float lambert = max(0.0, dot(incident, normals));
	
	vec3 viewDir = normalize((cameraPos - IN.worldPos));
	vec3 halfDir = normalize(incident + viewDir);
	
	float rFactor = max(0.0, dot(halfDir,normals));
	float sFactor = pow(rFactor,50);
	
	//Unlit
	fragColour[0] = texture(tex,IN.texCoords);
	//Normals
	fragColour[1] = vec4(normals,1);
	//Emissive
	fragColour[2] = vec4(lightColour.rgb * lambert, 1);
	//Specular
	fragColour[3] = vec4(((lightColour.rgb * sFactor) * 0.33f),1);
}