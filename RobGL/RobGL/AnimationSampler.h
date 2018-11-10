#pragma once
#include <External/glm/common.hpp>
#include <vector>
namespace rgl {
	class AnimationSampler
	{
	public:
		AnimationSampler();
		~AnimationSampler();

		glm::vec4 getSample(float time);

		void setInput(std::vector<float> input);
		void setOutput(std::vector<glm::vec4> output);
	private:
		std::vector<float> _input;
		std::vector<glm::vec4> _output;
	};
}
