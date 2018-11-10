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
		void setName(std::string name);

		std::string getName();
	private:
		std::string _name;
		std::vector<AnimationChannel> _channels;

	};
}
