#version 460 core

//uniform vec4 ambient;
uniform sampler2D tex;
uniform sampler2D emissiveTex;
uniform sampler2D specularTex;

in Vertex	{
	vec2 texCoords;
} IN;

out vec4 fragColour;

void main(void)	{
	vec3 diffuse = texture (tex , IN.texCoords).xyz ;
	vec3 light = texture (emissiveTex , IN.texCoords ).xyz ;
	vec3 specular = texture(specularTex , IN.texCoords ).xyz ;

	fragColour . xyz = diffuse * 0.2f; // ambient
	fragColour . xyz += diffuse * light; // lambert
	fragColour . xyz += specular; // Specular
    fragColour . a = 1.0;

}