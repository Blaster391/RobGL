#pragma once
#include "Mesh.h"
namespace rgl {
	class MeshHelpers
	{
	public:
		static Mesh* LoadMeshFromObj(std::string filename);
		static Mesh* GenerateTriangle();
		static Mesh* GenerateQuad();

	};
}
