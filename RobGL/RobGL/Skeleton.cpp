#include "Skeleton.h"

namespace rgl {

	Skeleton::Skeleton() : _jointMatrices(new glm::mat4[50])
	{

	}

	Skeleton::~Skeleton()
	{
		for (auto& j : _joints) {
			delete j.second;
		}
		_joints.clear();

		delete[] _jointMatrices;
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
	glm::mat4 * Skeleton::getJointMatrices()
	{
		for (auto& j : _joints) {
			_jointMatrices[j.first] = j.second->calculateJointMatrix();
		}

		return _jointMatrices;
	}
}