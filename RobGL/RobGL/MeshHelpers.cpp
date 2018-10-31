#include "MeshHelpers.h"
namespace rgl {
	Mesh * MeshHelpers::GenerateTriangle()
	{
		Mesh* m = new Mesh;

		std::vector<Vertex> verticies;
		Vertex v;
		v.Position = glm::vec3(0,0.5f,0);
		v.Colour = glm::vec4(1, 0, 0, 1);
		v.TexCoord = glm::vec2(0.5f, 1);
		verticies.push_back(v);

		v.Position = glm::vec3(-0.5f, 0, 0);
		v.Colour = glm::vec4(0, 1, 0, 1);
		v.TexCoord = glm::vec2(0, 0);
		verticies.push_back(v);

		v.Position = glm::vec3(0.5f, 0, 0);
		v.Colour = glm::vec4(0, 0, 1, 1);
		v.TexCoord = glm::vec2(1, 0);
		verticies.push_back(v);
		
		m->setVerticies(verticies);

		m->buffer();

		return m;
	}
}