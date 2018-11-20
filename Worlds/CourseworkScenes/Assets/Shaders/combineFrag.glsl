#version 460 core

uniform sampler2D colourTex;
uniform sampler2D emissiveTex;
uniform sampler2D specularTex;


in Vertex	{
	vec2 texCoords;
} IN;

out vec4 fragColour[4];

void main(void)	{

	
	vec3 diffuse = texture (colourTex , IN.texCoords).xyz ;
	vec3 light = texture (emissiveTex , IN.texCoords ).xyz ;
	vec3 specular = texture(specularTex , IN.texCoords ).xyz ;

	vec3 colour = diffuse * light; // lambert
	colour += specular; //Specular
	

	
	fragColour[0].xyz = diffuse * 0.1f; // ambient
	fragColour[0].xyz += colour; 
    fragColour[0].a = 1.0;
	
	fragColour[1] = vec4(0,0,0,0);
	fragColour[2] = vec4(0,0,0,0);
	fragColour[3] = vec4(0,0,0,0);
}