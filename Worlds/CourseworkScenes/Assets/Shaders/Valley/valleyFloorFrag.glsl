#version 460 core

uniform sampler2D tex;
uniform sampler2D flatTex;

uniform sampler2D shadowTex;

uniform vec4 lightColour;
uniform vec3 lightDirection;
uniform vec3 lightPosition;
uniform vec3 cameraPos;

uniform int useShadows;


uniform mat4 shadowMatrix;

in Vertex	{
	vec3 worldPos;
	vec2 texCoords;
	vec3 normals;
	vec4 shadowProj;
} IN;

out vec4 fragColour[4];

vec2 poissonDisk[64];
  
void main(void)	{


	poissonDisk[0] = vec2(-0.613392, 0.617481);
	poissonDisk[1] = vec2(0.170019, -0.040254);
	poissonDisk[2] = vec2(-0.299417, 0.791925);
	poissonDisk[3] = vec2(0.645680, 0.493210);
	poissonDisk[4] = vec2(-0.651784, 0.717887);
	poissonDisk[5] = vec2(0.421003, 0.027070);
	poissonDisk[6] = vec2(-0.817194, -0.271096);
	poissonDisk[7] = vec2(-0.705374, -0.668203);
	poissonDisk[8] = vec2(0.977050, -0.108615);
	poissonDisk[9] = vec2(0.063326, 0.142369);
	poissonDisk[10] = vec2(0.203528, 0.214331);
	poissonDisk[11] = vec2(-0.667531, 0.326090);
	poissonDisk[12] = vec2(-0.098422, -0.295755);
	poissonDisk[13] = vec2(-0.885922, 0.215369);
	poissonDisk[14] = vec2(0.566637, 0.605213);
	poissonDisk[15] = vec2(0.039766, -0.396100);
	poissonDisk[16] = vec2(0.751946, 0.453352);
	poissonDisk[17] = vec2(0.078707, -0.715323);
	poissonDisk[18] = vec2(-0.075838, -0.529344);
	poissonDisk[19] = vec2(0.724479, -0.580798);
	poissonDisk[20] = vec2(0.222999, -0.215125);
	poissonDisk[21] = vec2(-0.467574, -0.405438);
	poissonDisk[22] = vec2(-0.248268, -0.814753);
	poissonDisk[23] = vec2(0.354411, -0.887570);
	poissonDisk[24] = vec2(0.175817, 0.382366);
	poissonDisk[25] = vec2(0.487472, -0.063082);
	poissonDisk[26] = vec2(-0.084078, 0.898312);
	poissonDisk[27] = vec2(0.488876, -0.783441);
	poissonDisk[28] = vec2(0.470016, 0.217933);
	poissonDisk[29] = vec2(-0.696890, -0.549791);
	poissonDisk[30] = vec2(-0.149693, 0.605762);
	poissonDisk[31] = vec2(0.034211, 0.979980);
	poissonDisk[32] = vec2(0.503098, -0.308878);
	poissonDisk[33] = vec2(-0.016205, -0.872921);
	poissonDisk[34] = vec2(0.385784, -0.393902);
	poissonDisk[35] = vec2(-0.146886, -0.859249);
	poissonDisk[36] = vec2(0.643361, 0.164098);
	poissonDisk[37] = vec2(0.634388, -0.049471);
	poissonDisk[38] = vec2(-0.688894, 0.007843);
	poissonDisk[39] = vec2(0.464034, -0.188818);
	poissonDisk[40] = vec2(-0.440840, 0.137486);
	poissonDisk[41] = vec2(0.364483, 0.511704);
	poissonDisk[42] = vec2(0.034028, 0.325968);
	poissonDisk[43] = vec2(0.099094, -0.308023);
	poissonDisk[44] = vec2(0.693960, -0.366253);
	poissonDisk[45] = vec2(0.678884, -0.204688);
	poissonDisk[46] = vec2(0.001801, 0.780328);
	poissonDisk[47] = vec2(0.145177, -0.898984);
	poissonDisk[48] = vec2(0.062655, -0.611866);
	poissonDisk[49] = vec2(0.315226, -0.604297);
	poissonDisk[50] = vec2(-0.780145, 0.486251);
	poissonDisk[51] = vec2(-0.371868, 0.882138);
	poissonDisk[52] = vec2(0.200476, 0.494430);
	poissonDisk[53] = vec2(-0.494552, -0.711051);
	poissonDisk[54] = vec2(0.612476, 0.705252);
	poissonDisk[55] = vec2(-0.578845, -0.768792);
	poissonDisk[56] = vec2(-0.772454, -0.090976);
	poissonDisk[57] = vec2(0.504440, 0.372295);
	poissonDisk[58] = vec2(0.155736, 0.065157);
	poissonDisk[59] = vec2(0.391522, 0.849605);
	poissonDisk[60] = vec2(-0.620106, -0.328104);
	poissonDisk[61] = vec2(0.789239, -0.419965);
	poissonDisk[62] = vec2(-0.545396, 0.538133);
	poissonDisk[63] = vec2(-0.178564, -0.596057);

	float shadow = 1.0f;

	vec3 normals = normalize(IN.normals);

	vec3 incident = normalize(lightDirection);
	float lambert = max(0.0, dot(incident, normals));
	
	vec3 viewDir = normalize((IN.worldPos- cameraPos));
	vec3 halfDir = normalize(incident + viewDir);
	
	float rFactor = max(0.0, dot(halfDir,normals) - 0.3f);
	float sFactor = pow(rFactor,50);

	
	
	if(useShadows == 1){
		if(IN.shadowProj.w > 0.0){
			vec3 projCoords = IN.shadowProj.xyz / IN.shadowProj.w;
			projCoords = projCoords * 0.5 + 0.5; 
			float currentDepth = projCoords.z;  
			float closestDepth = texture(shadowTex, projCoords.xy).r;
			float bias = max(0.05 * (1.0 - dot(normals, lightDirection)), 0.005);  
			
			//Soften shadows with possion disk
			for (int i=0;i<64;i++){
			  if (texture( shadowTex, projCoords.xy + poissonDisk[i]/2000.0 ).r  <  currentDepth - bias ){
				shadow -= 0.0125;
				}
			}
			
		}
	}
	
	vec3 up = vec3(0,1,0);
	
	
	float blendAmount = max(0.0f, dot(normals, up));
	vec4 blendColour = texture(tex,IN.texCoords) * (1 - blendAmount) +texture(flatTex,IN.texCoords) * (blendAmount);
	
	
	//Unlit
	fragColour[0] = blendColour;
	
	//Normals
	fragColour[1] = vec4(normals,1);
	//Emissive
	fragColour[2] = vec4(lightColour.rgb * lambert * shadow, 1);
	//Specular
	fragColour[3] = vec4(((lightColour.rgb * sFactor) * 0.01f * shadow),1);

	
	//FOR DEBUGGING
	//fragColour[3] = vec4(debug.x,debug.y,debug.z,1);
}