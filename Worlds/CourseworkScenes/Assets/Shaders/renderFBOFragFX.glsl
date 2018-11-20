#version 460 core

uniform sampler2D overrideTex;

in Vertex	{
	in vec2 texCoords;
} IN;

out vec4 fragColour;

void main(void)	{
	fragColour = texture(overrideTex,IN.texCoords);
}