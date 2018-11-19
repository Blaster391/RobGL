#version 460 core

uniform sampler2D tex;
uniform int iteration;

in Vertex	{
	vec2 texCoords;
} IN;

out vec4 fragColour;


void main(void)	{
	vec4 colour = texture(tex,IN.texCoords);
	colour.b = 0;
	fragColour = colour;
}