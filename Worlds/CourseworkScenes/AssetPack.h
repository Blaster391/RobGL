#pragma once
#include <map>
#include <RobGL/AnimatedMesh.h>
#include <RobGL/Mesh.h>
#include <RobGL/Texture.h>
#include <RobGL/Cubemap.h>
#include <RobGL/Shader.h>

class AssetPack
{
public:
	AssetPack();
	~AssetPack();

	void loadSharedResources();
	void loadValleyResources();
	void loadSpaceResources();
	void loadAbductionResources();



private:
	std::map<std::string, rgl::Mesh*> _meshes;
	std::map<std::string, rgl::AnimatedMesh*> _animatedMeshes;

	std::map<std::string, rgl::Texture*> _textures;
	std::map<std::string, rgl::Cubemap*> _cubemaps;

	std::map<std::string, rgl::Shader*> _shaders;
};

