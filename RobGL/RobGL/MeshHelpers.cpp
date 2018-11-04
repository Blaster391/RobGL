#include "MeshHelpers.h"
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tinyobj/tiny_obj_loader.h"
#include <iostream>
#include <vector>

namespace rgl {
	Mesh* MeshHelpers::LoadMeshFromObj(std::string filename)
	{

		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::string err;
		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename.c_str());

		if (!err.empty()) { // `err` may contain warning message.
			std::cerr << err << std::endl;
		}

		if (!ret) {
			exit(1);
		}

		std::vector<Vertex> verticies;
		std::vector<Vertex> indices;

		// Loop over shapes
		for (size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces(polygon)
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				int fv = shapes[s].mesh.num_face_vertices[f];

				// Loop over vertices in the face.
				for (size_t v = 0; v < fv; v++) {
					Vertex vert;

					// access to vertex
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
					tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
					tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];
					vert.Position = (glm::vec3(vx, vy, vz));
					if (attrib.normals.size() > 3 * idx.normal_index) {
						tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0];
						tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1];
						tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2];
						vert.Normal = (glm::vec3(nx, ny, nz));
					}
					if (attrib.texcoords.size() > 2 * idx.texcoord_index) {
						tinyobj::real_t tx = attrib.texcoords[2 * idx.texcoord_index + 0];
						tinyobj::real_t ty = attrib.texcoords[2 * idx.texcoord_index + 1];
						vert.TexCoord = (glm::vec2(tx, ty));
					}
					/* Optional: vertex colors*/
					if (attrib.colors.size() > 3 * idx.vertex_index) {
						tinyobj::real_t red = attrib.colors[3 * idx.vertex_index + 0];
						tinyobj::real_t green = attrib.colors[3 * idx.vertex_index + 1];
						tinyobj::real_t blue = attrib.colors[3 * idx.vertex_index + 2];
						vert.Colour = (glm::vec4(blue, green, red, 1));
					}

					verticies.push_back(vert);
				}
				index_offset += fv;

				// per-face material
				shapes[s].mesh.material_ids[f];
			}
		}	

		Mesh* m = new Mesh();

		m->setVerticies(verticies);

		//TODO indicies

		m->buffer();
	
		return m;
	}


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
	Mesh * MeshHelpers::GenerateQuad()
	{
		Mesh* m = new Mesh;

		std::vector<Vertex> verticies;
		Vertex v;
		v.Position = glm::vec3(-0.5f, 0.5f, 0);
		v.Colour = glm::vec4(1, 0, 0, 1);
		v.TexCoord = glm::vec2(0, 1);
		verticies.push_back(v);

		v.Position = glm::vec3(0.5f, 0.5f, 0);
		v.Colour = glm::vec4(0, 1, 0, 1);
		v.TexCoord = glm::vec2(1, 1);
		verticies.push_back(v);

		v.Position = glm::vec3(-0.5f, -0.5f, 0);
		v.Colour = glm::vec4(0, 0, 1, 1);
		v.TexCoord = glm::vec2(0, 0);
		verticies.push_back(v);

		v.Position = glm::vec3(0.5f, -0.5f, 0);
		v.Colour = glm::vec4(0, 0, 1, 1);
		v.TexCoord = glm::vec2(1, 0);
		verticies.push_back(v);

		std::vector<unsigned int> indicies;
		indicies.push_back(0);
		indicies.push_back(1);
		indicies.push_back(2);
		indicies.push_back(2);
		indicies.push_back(1);
		indicies.push_back(3);


		m->setVerticies(verticies);
		m->setIndicies(indicies);

		m->buffer();

		return m;
	}
	Mesh * MeshHelpers::GenerateHeightMap(int vertsX, int vertsZ, float stepSize)
	{
		Mesh* m = GenerateHeightMapBase(vertsX, vertsZ, stepSize);

		m->buffer();

		return m;
	}
	Mesh * MeshHelpers::GenerateHeightMap(int vertsX, int vertsZ, float stepSize, std::string filename)
	{
		Mesh* m = GenerateHeightMapBase(vertsX, vertsZ, stepSize);

		m->buffer();

		return m;
	}
	Mesh * MeshHelpers::GenerateHeightMapBase(int vertsX, int vertsZ, float stepSize)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		for (int x = 0; x < vertsX; ++x) {
			 for (int z = 0; z < vertsZ; ++z) {
				int offset = (x * vertsX) + z;
				Vertex v;

				v.Position = glm::vec3(x * stepSize, 0, z * stepSize);
				
				//TODO better texCoords
				v.TexCoord = glm::vec2(x * stepSize, z * stepSize);
				

				vertices.push_back(v);
			}		}
		int numIndices = 0;
		
		 for (int x = 0; x < vertsX - 1; ++x) {
			 for (int z = 0; z < vertsZ - 1; ++z) {
				 int a = (x * (vertsX)) + z;
				 int b = ((x + 1) * (vertsX)) + z;
				 int c = ((x + 1) * (vertsX)) + (z + 1);
				int d = (x * (vertsX)) + (z + 1);
				
				indices.push_back(c);
				indices.push_back(b);
				indices.push_back(a);
				
				indices.push_back(a);
				indices.push_back(d);
				indices.push_back(c);
				
			}		}
		 Mesh* m = new Mesh();
		 m->setIndicies(indices);
		 m->setVerticies(vertices);

		return m;
	}
}