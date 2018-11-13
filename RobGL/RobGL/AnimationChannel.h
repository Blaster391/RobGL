#pragma once
#include "Joint.h"
#include "AnimationSampler.h"
namespace rgl {
	enum class AnimationChannelAction {
		Translate,
		Rotate,
		Scale
	};

	class AnimationChannel
	{
	public:
		AnimationChannel(Joint* joint, AnimationChannelAction action);
		~AnimationChannel();

		void update(float time);

		Joint* getTargetJoint();
		void setTargetJoint(Joint* j);
		AnimationChannelAction getAction();

		void setSampler(AnimationSampler sampler);
		AnimationSampler& getSampler();

		float getEndTime();

	private:
		Joint* _targetJoint;
		AnimationChannelAction _action;
		AnimationSampler _sampler;
	};

}

