#include "Joint.h"
#include <External/glm/gtc/matrix_transform.hpp>
#include <External/glm/gtc/quaternion.hpp>

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

	glm::mat4 Joint::calculateJointMatrix(glm::mat4 globalTransform)
	{
		auto gjt = getGlobalJointTransform();

		glm::mat4 jointMatrix = /*globalTransform **/ gjt * _inverseBind;

		if (_attachment != nullptr) {
			_attachment->setModelMatrix(globalTransform * gjt * _attachmentLocalTransform);
		}

		return jointMatrix;
	}

	void Joint::attachRenderObject(RenderObject * attachment, glm::mat4 localTransform)
	{
		_attachment = attachment;
		_attachmentLocalTransform = localTransform;
	}

	glm::mat4 Joint::getGlobalJointTransform()
	{
		glm::mat4 globalTransform(1);
		if (_parent != nullptr) {
			globalTransform = _parent->getGlobalJointTransform();
		}

		globalTransform = globalTransform * getLocalJointTransform();

		return globalTransform;
	}

	glm::mat4 Joint::getLocalJointTransform()
	{
		glm::quat rotate(_rotation.w, _rotation.x, _rotation.y, _rotation.z);
		return glm::translate(glm::mat4(1), _translation) *  glm::mat4_cast(rotate)  * glm::scale(glm::mat4(1), _scale);
	}


}
