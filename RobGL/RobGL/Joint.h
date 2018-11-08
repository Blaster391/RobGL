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

		glm::mat4 calculateJointMatrix();

	protected:
		std::vector<Joint*> _children;
		Joint* _parent = nullptr;
		std::vector<int> _childrenIndex;

		glm::vec4 _rotation;
		glm::vec3 _scale;
		glm::vec3 _translation;

		std::string _name;
		int _index;
		glm::mat4 _inverseBind;
	};

}