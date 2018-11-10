#pragma once
#include "Shader.h"
#include "ToScreenRenderPool.h"
#include <vector>

namespace rgl {
	class PostProcessingFX
		: private ToScreenRenderPool
	{
	public:
		PostProcessingFX(std::vector<Shader*> shaders, int iterations);
		~PostProcessingFX();

		void setIterations(int iterations) { _iterations = iterations; }

		virtual void process(float delta, int width, int height, GLuint flipTex, GLuint flopTex);

	private:
		int _iterations;
		GLuint _program;
		GLuint _flipTex;
		GLuint _flopTex;
	};
}


