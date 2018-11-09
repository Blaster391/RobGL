#pragma once
#include "AnimationChannel.h"
namespace rgl {
	class Animation
	{
	public:
		Animation();
		~Animation();

		void update(float time);

		void setChannels(std::vector<AnimationChannel> channels);

	private:
		std::vector<AnimationChannel> _channels;

	};
}

