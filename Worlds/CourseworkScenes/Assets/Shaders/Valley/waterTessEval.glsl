#version 460 core

uniform float time;
uniform float displacement;


layout(triangles, equal_spacing,ccw) in;

uniform mat4 modelMatrix ;
uniform mat4 viewMatrix ;
uniform mat4 projMatrix ;

in Vertex	{
	vec3 worldPos;
	vec2 texCoords;
	vec3 normals;
	vec4 shadowProj;
} IN[];

out Vertex	{
	vec3 worldPos;
	vec2 texCoords;
	vec3 normals;
	vec4 shadowProj;
} OUT;


vec3 QuadMixVec3 ( vec3 a , vec3 b , vec3 c , vec3 d ) {
	vec3 p0 = mix (a ,c , gl_TessCoord.x);
	vec3 p1 = mix (b ,d , gl_TessCoord.x);
	
	return mix ( p0 , p1 , gl_TessCoord.y);
}
  
void main(void)	{
	

	
	vec3 p0 = gl_TessCoord.x * gl_in [0].gl_Position.xyz;
	vec3 p1 = gl_TessCoord.y * gl_in [1].gl_Position.xyz;
	vec3 p2 = gl_TessCoord.z * gl_in [2].gl_Position.xyz;
	vec3 combinedPos = p0 + p1 + p2;
	combinedPos.y += sin((time + combinedPos.x * 0.1f + combinedPos.z * 0.05f)) * displacement;
		
		
	vec3 n0 = gl_TessCoord.x * IN[0].normals;
	vec3 n1 = gl_TessCoord.y * IN[1].normals;
	vec3 n2 = gl_TessCoord.z * IN[2].normals;
	vec3 combinedNorms = n0 + n1 + n2;
	combinedNorms.xz += cos((time + combinedPos.x * 0.1f + combinedPos.z * 0.05f)) * 0.05f * displacement;
		
	vec2 t0 = gl_TessCoord.x * IN[0].texCoords;
	vec2 t1 = gl_TessCoord.y * IN[1].texCoords;
	vec2 t2 = gl_TessCoord.z * IN[2].texCoords;
	vec2 combinedTexCoords = t0 + t1 + t2;
	combinedTexCoords = combinedTexCoords * 0.1f;
	
	vec4 s0 = gl_TessCoord.x * IN[0].shadowProj;
	vec4 s1 = gl_TessCoord.y * IN[1].shadowProj;
	vec4 s2 = gl_TessCoord.z * IN[2].shadowProj;
	vec4 combinedShadowProj = s0 + s1 + s2;
	
	vec4 worldPos = modelMatrix * vec4 ( combinedPos , 1);
	gl_Position = projMatrix * viewMatrix * worldPos ;
	
	OUT.worldPos = worldPos.xyz;
	OUT.texCoords = combinedTexCoords;
	OUT.normals = combinedNorms;
	OUT.shadowProj = combinedShadowProj;
}