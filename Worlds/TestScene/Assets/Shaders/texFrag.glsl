#version 460 core

uniform sampler2D tex;

in Vertex	{
	vec2 texCoords;
	vec3 normals;
} IN;

out vec4 fragColour[2];

void main(void)	{


	fragColour[0] = texture(tex,IN.texCoords);
	fragColour[1] = vec4(1,0,0,1);
}