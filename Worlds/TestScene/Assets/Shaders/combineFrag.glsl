#version 460 core

uniform int useShadows;

uniform sampler2D colourTex;
uniform sampler2D emissiveTex;
uniform sampler2D specularTex;
uniform sampler2DShadow shadowTex;

in Vertex	{
	vec2 texCoords;
	vec4 shadowProj;
} IN;

out vec4 fragColour;

void main(void)	{
	
	float shadow = 1.0f;
	
	vec3 diffuse = texture (colourTex , IN.texCoords).xyz ;
	vec3 light = texture (emissiveTex , IN.texCoords ).xyz ;
	vec3 specular = texture(specularTex , IN.texCoords ).xyz ;

	vec4 colour = diffuse * light; // lambert
	colour += specular; //Specular
	
	if(useShadows == 1){
		if(IN.shadowProj.w > 0.0){
			shadow = textureProj(shadowTex, IN.shadowProj);
			colour = colour * shadow;
		}
	}
	
	fragColour.xyz = diffuse * 0.1f; // ambient
	fragColour.xyz += colour; 
    fragColour.a = 1.0;

}