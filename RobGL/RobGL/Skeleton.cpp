#include "Skeleton.h"

namespace rgl {

	Skeleton::Skeleton()
	{
	}

	Skeleton::~Skeleton()
	{
		for (auto& j : _joints) {
			delete j.second;
		}
		_joints.clear();
	}
	void Skeleton::setJoints(std::vector<Joint*> joints)
	{
		for (auto& j : joints) {
			_joints[j->getIndex()] = j;
		}

		for (auto& j : joints) {
			std::vector<Joint*> children;
			for (auto& c : j->getChildIndices()) {
				children.push_back(_joints[c]);
			}
			j->setChildren(children);
		}

	}
}