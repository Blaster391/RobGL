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

	rgl::Shader* getShader(std::string s);
	rgl::Texture* getTexture(std::string t);
	rgl::Cubemap* getCubemap(std::string c);
	rgl::Mesh* getMesh(std::string m);
	rgl::AnimatedMesh* getAnimatedMesh(std::string m);
private:
	std::map<std::string, rgl::Mesh*> _meshes;
	std::map<std::string, rgl::AnimatedMesh*> _animatedMeshes;

	std::map<std::string, rgl::Texture*> _textures;
	std::map<std::string, rgl::Cubemap*> _cubemaps;

	std::map<std::string, rgl::Shader*> _shaders;
};

