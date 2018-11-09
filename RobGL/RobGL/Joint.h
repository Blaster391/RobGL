#pragma once
#include <vector>
#include <External/glm/common.hpp>
#include <External/glm/mat4x4.hpp>
namespace rgl {
	class Joint
	{
	public:
		Joint();
		~Joint();

		int getIndex();
		void setIndex(int index);
		void setInverseBindMatrix(glm::mat4 ib);

		void setChildren(std::vector<Joint*> children);

		std::vector<int> getChildIndices();
		void setChildIndices(std::vector<int> childrenIndex);
		void setName(std::string name);
		void setParent(Joint* p);

		void setRotation(glm::vec4 rotation);
		void setScale(glm::vec3 scale);
		void setTranslation(glm::vec3 translation);

		glm::mat4 calculateJointMatrix(glm::mat4 globalTransform);

	protected:
		std::vector<Joint*> _children;
		Joint* _parent = nullptr;
		std::vector<int> _childrenIndex;

		glm::vec4 _rotation = glm::vec4(1,1,1,0);
		glm::vec3 _scale = glm::vec3(1);
		glm::vec3 _translation = glm::vec3(0);

		std::string _name;
		int _index;
		glm::mat4 _inverseBind;

		glm::mat4 getGlobalJointTransform();
		glm::mat4 getLocalJointTransform();
	};

}