#version 460 core

uniform sampler2D tex;

uniform int iteration;
uniform vec2 pixelSize;

uniform sampler2D depthTex;
 
in Vertex	{
	vec2 texCoords;
} IN;

out vec4 fragColour;

const float weights [5] = float [](0.12 , 0.22 , 0.32 , 0.22 , 0.12);

void main(void)	{
	vec2 values[5];
	bool isVertical = (iteration % 2 == 0);
	
	float depth = texture2D(tex,IN.texCoords.xy).r;
	
	if(isVertical) {
	values = vec2 []( vec2 (0.0 , -pixelSize.y*2) ,
		vec2 (0.0 , -pixelSize.y *1) , vec2(0.0 ,0.0) ,
		vec2 (0.0 , pixelSize.y *1) , vec2(0.0 , pixelSize.y *2));
	}else{
	values = vec2 [](vec2(-pixelSize.x*2,0.0) ,
		vec2(-pixelSize.x * 1 , 0.0) , vec2(0,0.0) ,
		vec2(pixelSize.x*1,0.0) , vec2(pixelSize.x *2 ,0.0) );
	}


	
	for (int i = 0; i < 5; i ++ ) {
		vec2 mod = values[i] = values[i] * depth;
		vec4 tmp = texture2D(tex,IN.texCoords.xy + mod);
		fragColour += tmp * weights[i];
	}
}