#version 460 core

uniform sampler2D tex;

in Vertex	{
	vec2 texCoords;
} IN;

out vec4 fragColour;

void main(void)	{	

	vec4 value = texture(tex,IN.texCoords).rgba;

	if(value.a == 0){
		discard;
	}

	fragColour = value;
}