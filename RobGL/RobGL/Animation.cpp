#include "Animation.h"


namespace rgl {
	Animation::Animation()
	{
	}


	Animation::~Animation()
	{
	}

	void Animation::update(float delta)
	{
		_currentTime += delta;
		for (auto& c : _channels) {
			c.update(_currentTime);
		}

		if (_currentTime > _finishTime) {
			for (auto& c : _channels) {
				c.getSampler().reset();
			}
			_currentTime = 0;
		}

	}
	void Animation::setChannels(std::vector<AnimationChannel> channels)
	{
		_channels = channels;

		for (auto& c : channels) {
			float endTime = c.getEndTime();
			if (endTime > _finishTime) {
				_finishTime = endTime;
			}
		}
	}
	void Animation::setName(std::string name)
	{
		_name = name;
	}
	std::string Animation::getName()
	{
		return _name;
	}
}