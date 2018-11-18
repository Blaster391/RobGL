#version 460 core

uniform sampler2D tex;
uniform sampler2D textTex;
uniform vec3 textColor;





in Vertex	{
	vec2 texCoords;
} IN;

out vec4 fragColour;

void main(void)	{
	
	float colour = texture(tex, IN.texCoords).r;

	vec4 sampled = vec4(1.0, 1.0, 1.0, colour);
	
	fragColour = texture(tex, IN.texCoords);
}