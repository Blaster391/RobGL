#pragma once
#include <string>
#include <map>
#include "Joint.h"

namespace rgl {

	class Skeleton
	{
	public:
		Skeleton();
		~Skeleton();


		void setJoints(Joint* root, std::vector<Joint*> joints);

		glm::mat4* getJointMatrices();

		void setGlobalTransform(glm::mat4 transform);

	private:
		std::map<int, Joint*> _joints;
		Joint* _root;
		glm::mat4* _jointMatrices;
		glm::mat4 _globalTransform;
	};
}
