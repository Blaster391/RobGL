#include "Skeleton.h"

namespace rgl {

	Skeleton::Skeleton() : _jointMatrices(new glm::mat4[50])
	{
		for (int i = 0; i < 50; ++i) {
			_jointMatrices[i] = glm::mat4(1);
		}
	}

	Skeleton::~Skeleton()
	{
		for (auto& j : _joints) {
			delete j.second;
		}
		_joints.clear();

		delete[] _jointMatrices;
	}
	void Skeleton::setJoints(Joint* root, std::vector<Joint*> joints)
	{
		_root = root;

		for (auto& j : joints) {
			_joints[j->getIndex()] = j;
			//Use root as default parent
			j->setParent(_root);
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
			_jointMatrices[j.first] = j.second->calculateJointMatrix(_globalTransform);
		}

		return _jointMatrices;
	}
	void Skeleton::setGlobalTransform(glm::mat4 transform)
	{
		_globalTransform = transform;
	}
}