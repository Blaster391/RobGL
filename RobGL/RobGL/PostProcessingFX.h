#pragma once
#include "Shader.h"
#include "ToScreenRenderPool.h"
#include <vector>

namespace rgl {
	class PostProcessingFX
		: protected ToScreenRenderPool
	{
	public:
		PostProcessingFX(std::vector<Shader*> shaders, int iterations);
		~PostProcessingFX();

		void setIterations(int iterations) { _iterations = iterations; }

		virtual void process(float delta, GLuint& displayTex, GLuint& processTex);

	private:
		int _iterations;
	};
}


