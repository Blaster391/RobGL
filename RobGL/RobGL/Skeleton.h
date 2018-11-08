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


		void setJoints(std::vector<Joint*> joints);

	private:
		std::map<int, Joint*> _joints;
		Joint* _root;
	};
}
