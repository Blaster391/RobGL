#version 460 core

uniform sampler2D tex;

in Vertex	{
	vec3 worldPos;
	vec2 texCoords;
	vec3 normals;
	vec4 shadowProj;
} IN;

out vec4 fragColour[4];

void main(void)	{

	fragColour[0] = texture(tex,IN.texCoords);
	fragColour[1] = vec4(IN.normals,1);
}