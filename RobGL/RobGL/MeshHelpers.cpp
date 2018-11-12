#include "MeshHelpers.h"
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tinyobj/tiny_obj_loader.h"
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include "tinygltf/tiny_gltf.h"
#include <iostream>
#include <vector>
#include <External/stb/stb_image.h>



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
		std::vector<unsigned int> indices;

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

	Mesh * MeshHelpers::LoadMeshFromGLTF(std::string filename)
	{
		tinygltf::Model model;
		tinygltf::TinyGLTF gltf_ctx;

		std::string err;
		std::string warn;


		bool ret = gltf_ctx.LoadASCIIFromFile(&model, &err, &warn, filename.c_str());

		std::vector<Vertex> verticies;
		std::vector<unsigned int> indices;

		Mesh* m = new Mesh();

		std::cout << "meshes(item=" << model.meshes.size() << ")" << std::endl;
		if (model.meshes.size() == 0) {
			return nullptr;
		}

		auto& mesh = model.meshes[0];

		std::cout << "name     : " << mesh.name << std::endl;
		std::cout << "primitives(items=" << mesh.primitives.size() << "): " << std::endl;

		std::cout << mesh.primitives[0].indices << std::endl;

		for (auto& at : mesh.primitives[0].attributes) {
			std::cout << at.first << std::endl;
			std::cout << at.second << std::endl;
		}

		int indicesAccessor = mesh.primitives[0].indices;
		int positionAccessor = mesh.primitives[0].attributes["POSITION"];
		int texCoordAccessor = mesh.primitives[0].attributes["TEXCOORD_0"];

		std::cout << model.accessors[indicesAccessor].count << std::endl;
		std::cout << model.accessors[positionAccessor].count << std::endl;
		std::cout << model.accessors[texCoordAccessor].count << std::endl;

		auto positionBV = model.bufferViews[model.accessors[positionAccessor].bufferView];
		auto texCoordBV = model.bufferViews[model.accessors[texCoordAccessor].bufferView];

		auto positionInterator = (glm::vec3*)(model.buffers[positionBV.buffer].data.data() + positionBV.byteOffset);
		auto texCoordInterator = (glm::vec2*)(model.buffers[texCoordBV.buffer].data.data() + texCoordBV.byteOffset);

		for (auto i = 0; i < model.accessors[positionAccessor].count; i++){
			Vertex v;

			v.Position = *(positionInterator + i);
			v.TexCoord = *(texCoordInterator + i);

			v.TexCoord.y = 1-v.TexCoord.y;

			verticies.push_back(v);
		}

		auto indicesBV = model.bufferViews[model.accessors[indicesAccessor].bufferView];
		auto indicesInterator = (short*)(model.buffers[indicesBV.buffer].data.data() + indicesBV.byteOffset);
		for (auto i = 0; i < model.accessors[indicesAccessor].count; i++) {
			indices.push_back(*(indicesInterator + i));
		}

		m->setVerticies(verticies);
		m->setIndicies(indices);
		

		m->buffer();

		return m;
	}

	AnimatedMesh * MeshHelpers::LoadAnimatedMeshFromGLTF(std::string filename)
	{
		tinygltf::Model model;
		tinygltf::TinyGLTF gltf_ctx;

		std::string err;
		std::string warn;


		bool ret = gltf_ctx.LoadASCIIFromFile(&model, &err, &warn, filename.c_str());

		std::vector<Vertex> verticies;
		std::vector<unsigned int> indices;
		std::vector<VertexWeightData> weightData;


		AnimatedMesh* m = new AnimatedMesh();

		std::cout << "meshes(item=" << model.meshes.size() << ")" << std::endl;
		if (model.meshes.size() == 0) {
			return nullptr;
		}

		auto& mesh = model.meshes[0];

		std::cout << "name     : " << mesh.name << std::endl;
		std::cout << "primitives(items=" << mesh.primitives.size() << "): " << std::endl;

		std::cout << mesh.primitives[0].indices << std::endl;

		for (auto& at : mesh.primitives[0].attributes) {
			std::cout << at.first << std::endl;
			std::cout << at.second << std::endl;
		}

		int indicesAccessor = mesh.primitives[0].indices;
		int positionAccessor = mesh.primitives[0].attributes["POSITION"];
		int texCoordAccessor = mesh.primitives[0].attributes["TEXCOORD_0"];
		int weightsAccessor = mesh.primitives[0].attributes["WEIGHTS_0"];
		int jointsAccessor = mesh.primitives[0].attributes["JOINTS_0"];

		std::cout << model.accessors[indicesAccessor].count << std::endl;
		std::cout << model.accessors[positionAccessor].count << std::endl;
		std::cout << model.accessors[texCoordAccessor].count << std::endl;

		auto positionBV = model.bufferViews[model.accessors[positionAccessor].bufferView];
		auto texCoordBV = model.bufferViews[model.accessors[texCoordAccessor].bufferView];
		auto weightsBV = model.bufferViews[model.accessors[weightsAccessor].bufferView];
		auto jointsBV = model.bufferViews[model.accessors[jointsAccessor].bufferView];


		auto positionInterator = (glm::vec3*)(model.buffers[positionBV.buffer].data.data() + positionBV.byteOffset);
		auto texCoordInterator = (glm::vec2*)(model.buffers[texCoordBV.buffer].data.data() + texCoordBV.byteOffset);
		auto weightsInterator = (glm::vec4*)(model.buffers[weightsBV.buffer].data.data() + weightsBV.byteOffset);
		auto jointsInterator = (glm::u16vec4*)(model.buffers[jointsBV.buffer].data.data() + jointsBV.byteOffset);

	

		for (auto i = 0; i < model.accessors[positionAccessor].count; i++) {
			Vertex v;

			VertexWeightData vwd;

			v.Position = *(positionInterator + i);
			v.TexCoord = *(texCoordInterator + i);
			//Fix tex coords
			v.TexCoord.y = 1 - v.TexCoord.y;

			verticies.push_back(v);
			vwd.Joints = *(jointsInterator + i); 
			vwd.Weights = *(weightsInterator + i);

			//std::cout << vwd.Joints.x << "," << vwd.Joints.y << "," << vwd.Joints.z << "," << vwd.Joints.w << std::endl;

			weightData.push_back(vwd);
		}

		auto indicesBV = model.bufferViews[model.accessors[indicesAccessor].bufferView];
		auto indicesInterator = (short*)(model.buffers[indicesBV.buffer].data.data() + indicesBV.byteOffset);
		for (auto i = 0; i < model.accessors[indicesAccessor].count; i++) {
			indices.push_back(*(indicesInterator + i));
		}

		m->setVerticies(verticies);
		m->setIndicies(indices);
		m->setVerticiesWeightData(weightData);

		if (model.skins.size() > 0) {

			auto& skin = model.skins[0];


			auto inverseBindAccessor = model.accessors[skin.inverseBindMatrices];
			


			auto inverseBindBV = model.bufferViews[model.accessors[inverseBindAccessor.bufferView].bufferView];
			auto inverseBindIterator = (glm::mat4*)(model.buffers[inverseBindBV.buffer].data.data() + inverseBindBV.byteOffset);

			std::vector<Joint*> joints;

			std::map<int, int> jointMap;
			for (int i = 0; i < skin.joints.size(); ++i) {
				jointMap[skin.joints[i]] = i;
			}

			for (int i = 0; i < inverseBindAccessor.count; ++i) {
				Joint* j = new Joint;
				
				glm::mat4 inverseBind = *(inverseBindIterator + i);
				j->setInverseBindMatrix(inverseBind);

				auto& node = model.nodes[skin.joints[i]];

				j->setName(node.name);
				j->setIndex(jointMap[skin.joints[i]]);
				std::vector<int> children;
				for (auto& c : node.children) {
					children.push_back(jointMap[c]);
				}

				j->setChildIndices(children);

				if (node.scale.size() > 2) {
					j->setScale(glm::vec3(node.scale[0], node.scale[1], node.scale[2]));
				}
				if (node.rotation.size() > 3) {
					j->setRotation(glm::vec4(node.rotation[0], node.rotation[1], node.rotation[2], node.rotation[3]));
				}
				if (node.translation.size() > 2) {
					j->setTranslation(glm::vec3(node.translation[0], node.translation[1], node.translation[2]));
				}

				joints.push_back(j);
				//TODO root node?
			}

			//auto& rootNode = model.nodes[skin.skeleton];
			auto& rootNode = model.nodes[skin.skeleton];
			Joint* root = new Joint;
			root->setIndex(-1);
			root->setName(rootNode.name);
			if (rootNode.scale.size() > 3) {
				root->setScale(glm::vec3(rootNode.scale[0], rootNode.scale[1], rootNode.scale[2]));
			}
			if (rootNode.rotation.size() > 3) {
				root->setRotation(glm::vec4(rootNode.rotation[0], rootNode.rotation[1], rootNode.rotation[2], rootNode.rotation[3]));
			}
			if (rootNode.translation.size() > 2) {
				root->setTranslation(glm::vec3(rootNode.translation[0], rootNode.translation[1], rootNode.translation[2]));
			}


			root->setInverseBindMatrix(glm::mat4(1));

			Skeleton* s = new Skeleton;
			s->setJoints(root, joints);


			std::vector<Animation> animations;
			for (auto& a : model.animations) {
				Animation animation;
				animation.setName(a.name);
				std::vector<AnimationChannel> channels;
				for (auto& c : a.channels) {
					auto& joint = joints[jointMap[c.target_node]];

					AnimationChannelAction action;
					if (c.target_path == "rotation") {
						action = AnimationChannelAction::Rotate;
					}
					else if (c.target_path == "scale") {
						action = AnimationChannelAction::Scale;
					}
					else {
						action = AnimationChannelAction::Translate;
					}

					AnimationChannel channel(joint, action);


					AnimationSampler sampler;
					auto& s = a.samplers[c.sampler];
					//TODO Currently only supports Linear sampling
					//Also no support for changing weights

					std::vector<float> input;
					std::vector<glm::vec4> output;

					auto inputAccessor = model.accessors[s.input];
					auto inputBV = model.bufferViews[model.accessors[inputAccessor.bufferView].bufferView];
					auto inputIterator = (float*)(model.buffers[inputBV.buffer].data.data() + inputBV.byteOffset);

					for (int i = 0; i < inputAccessor.count; ++i) {
						input.push_back(*(inputIterator + i));
					}

					auto outputAccessor = model.accessors[s.output];
					auto outputBV = model.bufferViews[model.accessors[outputAccessor.bufferView].bufferView];

					if (action == AnimationChannelAction::Rotate) {
						auto outputIterator = (glm::vec4*)(model.buffers[outputBV.buffer].data.data() + outputBV.byteOffset);
						for (int i = 0; i < outputAccessor.count; ++i) {
							output.push_back(*(outputIterator + i));
						}
					}
					else {
						auto outputIterator = (glm::vec3*)(model.buffers[outputBV.buffer].data.data() + outputBV.byteOffset);
						for (int i = 0; i < outputAccessor.count; ++i) {
							output.push_back(glm::vec4(*(outputIterator + i),1));
						}
					}
				
					sampler.setInput(input);
					sampler.setOutput(output);

					channel.setSampler(sampler);
					channels.push_back(channel);
				}
				animation.setChannels(channels);
				animations.push_back(animation);
			}

			m->setSkeleton(s);
			m->setAnimations(animations);

		}

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
		v.Position = glm::vec3(-1, 1, 0);
		v.Colour = glm::vec4(1, 0, 0, 1);
		v.TexCoord = glm::vec2(0, 1);
		verticies.push_back(v);

		v.Position = glm::vec3(1, 1, 0);
		v.Colour = glm::vec4(0, 1, 0, 1);
		v.TexCoord = glm::vec2(1, 1);
		verticies.push_back(v);

		v.Position = glm::vec3(-1, -1, 0);
		v.Colour = glm::vec4(0, 0, 1, 1);
		v.TexCoord = glm::vec2(0, 0);
		verticies.push_back(v);

		v.Position = glm::vec3(1, -1, 0);
		v.Colour = glm::vec4(0, 0, 1, 1);
		v.TexCoord = glm::vec2(1, 0);
		verticies.push_back(v);

		std::vector<unsigned int> indicies;
		indicies.push_back(0);
		indicies.push_back(2);
		indicies.push_back(1);
		indicies.push_back(2);
		indicies.push_back(3);
		indicies.push_back(1);


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
	Mesh * MeshHelpers::GenerateHeightMap(int vertsX, int vertsZ, float stepSize, std::string filename, float yScale)
	{
		Mesh* m = GenerateHeightMapBase(vertsX, vertsZ, stepSize);



		int w;
		int h;
		int comp;

		unsigned char* image = stbi_load(filename.c_str(), &w, &h, &comp, STBI_grey);

		unsigned char maxVal = ~0;


		int heightStep = h / vertsZ;
		int widthStep = w / vertsX;

		auto verts = m->getVertices();

		for (int x = 0; x < vertsX; ++x) {
			for (int z = 0; z < vertsZ; ++z) {
				unsigned short y = image[x*widthStep + (z* heightStep)*vertsX];
				verts[x + z * vertsX].Position.y = ((float)y/ maxVal) * yScale;

			}
		}


		m->setVerticies(verts);

		stbi_image_free(image);

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
			}
		}

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
				
			}
		}

		 Mesh* m = new Mesh();
		 m->setIndicies(indices);
		 m->setVerticies(vertices);

		return m;
	}
}