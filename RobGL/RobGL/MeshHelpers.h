#pragma once
#include "Mesh.h"
namespace rgl {
	class MeshHelpers
	{
	public:
		static Mesh* LoadMeshFromObj(std::string filename);
		static Mesh* GenerateTriangle();
		static Mesh* GenerateQuad();
		static Mesh* GenerateHeightMap(int vertsX, int vertsZ, float stepSize);
		static Mesh* GenerateHeightMap(int vertsX, int vertsZ, float stepSize, std::string filename, float yScale = 10);
	private:
		static Mesh* GenerateHeightMapBase(int vertsX, int vertsZ, float stepSize);
	};
}
