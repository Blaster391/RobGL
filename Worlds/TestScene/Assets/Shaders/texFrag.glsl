#version 460 core

uniform sampler2D tex;

in Vertex	{
	vec2 texCoords;
} IN;

out vec4 fragColour;

void main(void)	{	
	fragColour = texture(tex,IN.texCoords);
}