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

		float lastTime = getEndTime();

		if (time > lastTime) {
			return _output[_input.size() - 1];
		}

		int index = -1;
		for (int i = _lastSample; i < _input.size(); ++i) {
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

		startTime = _input[_lastSample];
		startPos = _output[_lastSample];
		
		float lerpValue = startTime / endTime;

		_lastSample = index;

		return glm::mix(startPos, endPos, lerpValue);
	}

	void AnimationSampler::reset()
	{
		_lastSample = 0;
	}

	void AnimationSampler::setInput(std::vector<float> input)
	{
		_input = input;
	}

	void AnimationSampler::setOutput(std::vector<glm::vec4> output)
	{
		_output = output;
	}

	float AnimationSampler::getEndTime()
	{
		return _input[_input.size() - 1];
	}

}

