#include "AnimationChannel.h"

namespace rgl {
	AnimationChannel::AnimationChannel(Joint * joint, AnimationChannelAction action)
		: _targetJoint(joint), _action(action)
	{
	}
	AnimationChannel::~AnimationChannel()
	{
	}

	void AnimationChannel::update(float time)
	{
		glm::vec4 sample = _sampler.getSample(time);

		switch (_action) {
			case AnimationChannelAction::Translate:
				_targetJoint->setTranslation(sample);
				break;
			case AnimationChannelAction::Rotate:
				_targetJoint->setRotation(sample);
				break;
			case AnimationChannelAction::Scale:
				_targetJoint->setScale(sample);
				break;
		}

	}

	Joint * AnimationChannel::getTargetJoint()
	{
		return _targetJoint;
	}

	void AnimationChannel::setTargetJoint(Joint * j)
	{
		_targetJoint = j;
	}

	AnimationChannelAction AnimationChannel::getAction()
	{
		return _action;
	}

	void AnimationChannel::setSampler(AnimationSampler sampler)
	{
		_sampler = sampler;
	}

	AnimationSampler& AnimationChannel::getSampler()
	{
		return _sampler;
	}

	float AnimationChannel::getEndTime()
	{
		return _sampler.getEndTime();
	}

}

