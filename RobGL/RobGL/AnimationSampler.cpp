#include "AnimationSampler.h"
#include <External/glm/glm.hpp>
namespace rgl {
	AnimationSampler::AnimationSampler()
	{
	}


	AnimationSampler::~AnimationSampler()
	{
	}

	glm::vec4 AnimationSampler::getSample(float time)
	{
		if (_input.size() < 1) {
			return glm::vec4(1);
		}

		float lastTime = _input[_input.size() - 1];

		if (time > lastTime) {
			return _output[_input.size() - 1];
		}

		//TODO remember value for effeciency
		int index = -1;
		for (int i = 0; i < _input.size(); ++i) {
			if (_input[i] > time) {
				break;
			}
			index = i;
		}

		if (index == _input.size() - 1) {
			return _output[_input.size() - 1];
		}

		float startTime = 0;
		float endTime = _input[index + 1];

		glm::vec4 startPos = glm::vec4();
		glm::vec4 endPos = _output[index + 1];
		if (index > -1) {
			startTime = _input[index];
			startPos = _output[index];
		}
		float lerpValue = startTime / endTime;

		return glm::mix(startPos, endPos, lerpValue);
	}

	void AnimationSampler::setInput(std::vector<float> input)
	{
		_input = input;
	}

	void AnimationSampler::setOutput(std::vector<glm::vec4> output)
	{
		_output = output;
	}

}

