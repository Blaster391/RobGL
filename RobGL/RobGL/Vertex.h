#pragma once
#include <External/glm/common.hpp>
namespace rgl {
	struct Vertex
	{
	public:
		glm::vec3 Position;
		glm::vec4 Colour;
		glm::vec2 TexCoord;
		glm::vec3 Normal = glm::vec3(0);
	};
}
