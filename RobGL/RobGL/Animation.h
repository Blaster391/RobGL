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

		std::vector<AnimationChannel>& getChannels() {
			return _channels;
		}
	private:
		std::string _name;
		std::vector<AnimationChannel> _channels;
		float _currentTime = 0;
		float _finishTime = 0;
	};
}

