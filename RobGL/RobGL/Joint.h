#pragma once
#include <vector>
namespace rgl {
	class Joint
	{
	public:
		Joint();
		~Joint();
	protected:
		std::vector<Joint*> _children;
		Joint* _parent;
	};

}