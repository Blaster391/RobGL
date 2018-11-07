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
	private:
		std::map<std::string, Joint*> _joints;
	};
}
