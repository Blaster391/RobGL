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
	
	
	vec4 texColour =  texture(tex, IN.texCoords);
	
	if(texColour.a < 0.5f){
		discard;
	}
	
	vec4 combinedColour = texColour * IN.colour;
	combinedColour.a = 1;

	
	//Unlit
	fragColour[0] = combinedColour;
	//Normals
	fragColour[1] = vec4(0,0,0,1);
	//Emissive
	fragColour[2] = combinedColour;
	//Specular
	fragColour[3] = vec4(0,0,0,1);
}