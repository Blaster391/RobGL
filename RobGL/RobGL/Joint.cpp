#include "Joint.h"

namespace rgl {

	Joint::Joint()
	{
	}


	Joint::~Joint()
	{
	}
	int Joint::getIndex()
	{
		return _index;
	}
	void Joint::setIndex(int index)
	{
		_index = index;
	}
	void Joint::setInverseBindMatrix(glm::mat4 ib)
	{
		_inverseBind = ib;
	}
	void Joint::setChildren(std::vector<Joint*> children)
	{
		_children = children;
		for (auto& c : _children) {
			c->setParent(this);
		}
	}
	std::vector<int> Joint::getChildIndices()
	{
		return _childrenIndex;
	}
	void Joint::setChildIndices(std::vector<int> childrenIndex)
	{
		_childrenIndex = childrenIndex;
	}
	void Joint::setName(std::string name)
	{
		_name = name;
	}
	void Joint::setParent(Joint * p)
	{
		_parent = p;
	}
	void Joint::setRotation(glm::vec4 rotation)
	{
		_rotation = rotation;
	}
	void Joint::setScale(glm::vec3 scale)
	{
		_scale = scale;
	}
	void Joint::setTranslation(glm::vec3 translation)
	{
		_translation = translation;
	}

	glm::mat4 Joint::calculateJointMatrix()
	{
		//jointMatrix = inverse(globalTransform) * golbalJointTransform * inverseBindMatrix;
		return glm::mat4();
	}


}
