#version 460 core

uniform sampler2D	tex;
uniform float 		width;
uniform float 		height;


in Vertex	{
	vec2 texCoords;
} IN;

out vec4 fragColour;

void main(void) 
{
	vec4 n[9];
	
	float w = 1.0 / width;
	float h = 1.0 / height;
	
	n[0] = texture2D(tex, IN.texCoords + vec2( -w, -h));
	n[1] = texture2D(tex, IN.texCoords + vec2(0.0, -h));
	n[2] = texture2D(tex, IN.texCoords + vec2(  w, -h));
	n[3] = texture2D(tex, IN.texCoords + vec2( -w, 0.0));
	n[4] = texture2D(tex, IN.texCoords);
	n[5] = texture2D(tex, IN.texCoords + vec2(  w, 0.0));
	n[6] = texture2D(tex, IN.texCoords + vec2( -w, h));
	n[7] = texture2D(tex, IN.texCoords + vec2(0.0, h));
	n[8] = texture2D(tex, IN.texCoords + vec2(  w, h));

	vec4 sobel_edge_h = n[2] + (2.0*n[5]) + n[8] - (n[0] + (2.0*n[3]) + n[6]);
  	vec4 sobel_edge_v = n[0] + (2.0*n[1]) + n[2] - (n[6] + (2.0*n[7]) + n[8]);
	vec4 sobel = sqrt((sobel_edge_h * sobel_edge_h) + (sobel_edge_v * sobel_edge_v));

	fragColour = vec4( 1.0 - sobel.rgb, 1.0 );
}