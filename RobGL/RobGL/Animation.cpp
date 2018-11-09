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
		if (time > 10) {
			time = 0;
		}

	}
	void Animation::setChannels(std::vector<AnimationChannel> channels)
	{
		_channels = channels;
	}
}