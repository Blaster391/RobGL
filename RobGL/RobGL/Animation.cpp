#include "Animation.h"


namespace rgl {
	Animation::Animation()
	{
	}


	Animation::~Animation()
	{
	}

	float time = 0;
	void Animation::update(float delta)
	{
		//TODO loop
		time += delta;
		for (auto& c : _channels) {
			c.update(time);
		}
		if (time > 5) {
			time = 0;
		}

	}
	void Animation::setChannels(std::vector<AnimationChannel> channels)
	{
		_channels = channels;
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