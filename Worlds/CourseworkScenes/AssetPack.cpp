#include "AssetPack.h"

#include <RobGL/TextureLoader.h>
#include <RobGL/MeshHelpers.h>

AssetPack::AssetPack()
{
}


AssetPack::~AssetPack()
{
	for (auto& s : _shaders) {
		delete s.second;
	}

}

void AssetPack::loadSharedResources()
{
	//### SHADERS ###//
	_shaders["ColouredVertex"] = new rgl::Shader("Assets/Shaders/colourVert.glsl", GL_VERTEX_SHADER);
	_shaders["ColouredFragment"] = new rgl::Shader("Assets/Shaders/colourFrag.glsl", GL_FRAGMENT_SHADER);

	_shaders["TexturedVertex"] = new rgl::Shader("Assets/Shaders/texVert.glsl", GL_VERTEX_SHADER);
	_shaders["TexturedFragment"] = new rgl::Shader("Assets/Shaders/texFrag.glsl", GL_FRAGMENT_SHADER);
	_shaders["UnlitTexturedFragment"] = new rgl::Shader("Assets/Shaders/litTexFrag.glsl", GL_FRAGMENT_SHADER);

	_shaders["AnimatedVertex"] = new rgl::Shader("Assets/Shaders/animatedVert.glsl", GL_VERTEX_SHADER);

	_shaders["TexturedVertex_NO_MVP"] = new rgl::Shader("Assets/Shaders/texVertNoMVP.glsl", GL_VERTEX_SHADER);

	//Lighting
	_shaders["PointLightVertex"] = new rgl::Shader("Assets/Shaders/pointLightVert.glsl", GL_VERTEX_SHADER);
	_shaders["PointLightFragment"] = new rgl::Shader("Assets/Shaders/pointLightFrag.glsl", GL_FRAGMENT_SHADER);

	_shaders["ShadowMapVertex"] = new rgl::Shader("Assets/Shaders/shadowMapVert.glsl", GL_VERTEX_SHADER);
	_shaders["ShadowMapFragment"] = new rgl::Shader("Assets/Shaders/shadowMapFrag.glsl", GL_FRAGMENT_SHADER);

	_shaders["LightingCombineVertex"] = new rgl::Shader("Assets/Shaders/combineVert.glsl", GL_VERTEX_SHADER);
	_shaders["LightingCombineFragment"] = new rgl::Shader("Assets/Shaders/combineFrag.glsl", GL_FRAGMENT_SHADER);

	//Text
	_shaders["TextVertex"] = new rgl::Shader("Assets/Shaders/textVert.glsl", GL_VERTEX_SHADER);
	_shaders["TextFragment"] = new rgl::Shader("Assets/Shaders/textFrag.glsl", GL_FRAGMENT_SHADER);

	//Post processing
	_shaders["SkyboxVertexFX"] = new rgl::Shader("Assets/Shaders/skyboxVertFX.glsl", GL_VERTEX_SHADER);
	_shaders["SkyboxFragmentFX"] = new rgl::Shader("Assets/Shaders/skyboxFragFX.glsl", GL_FRAGMENT_SHADER);

	_shaders["BlurFragmentFX"] = new rgl::Shader("Assets/Shaders/blurFragFX.glsl", GL_FRAGMENT_SHADER);
	_shaders["SobelFragmentFX"] = new rgl::Shader("Assets/Shaders/sobelFragFX.glsl", GL_FRAGMENT_SHADER);

	//### Models ###//
	_meshes["triangle"] = rgl::MeshHelpers::GenerateTriangle();
	_meshes["quad"] = rgl::MeshHelpers::GenerateQuad();
	_meshes["anky"] = rgl::MeshHelpers::LoadMeshFromGLTF("Assets/Models/ankyanim.gltf");
	_meshes["sphere"] = rgl::MeshHelpers::LoadMeshFromObj("Assets/Models/ico.obj");

	//Hats
	_meshes["cowboyHat"] = rgl::MeshHelpers::LoadMeshFromObj("Assets/Models/hat.obj");

	//Animated Meshes
	_animatedMeshes["anky"] = rgl::MeshHelpers::LoadAnimatedMeshFromGLTF("Assets/Models/ankyanim.gltf");

	//### Textures ###//
	_textures["box"] = rgl::TextureLoader::LoadFromFile("Assets/Textures/test.png", false, true);
	_textures["stainedglass"] = rgl::TextureLoader::LoadFromFile("Assets/Textures/stainedglass.tga", true, true);
	_textures["anky"] = rgl::TextureLoader::LoadFromFile("Assets/Textures/Anky.png", true, true);
	_textures["particle"] = rgl::TextureLoader::LoadFromFile("Assets/Textures/particle.tga", true, false);

	

}

void AssetPack::loadValleyResources()
{
	//Skybox
	_cubemaps["valley"] = rgl::TextureLoader::LoadCubemapFromFile({
		"Assets/Textures/cubemaps/Valley/rusted_west.jpg",
		"Assets/Textures/cubemaps/Valley/rusted_east.jpg",
		"Assets/Textures/cubemaps/Valley/rusted_up.jpg",
		"Assets/Textures/cubemaps/Valley/rusted_down.jpg",
		"Assets/Textures/cubemaps/Valley/rusted_south.jpg" ,
		"Assets/Textures/cubemaps/Valley/rusted_north.jpg" }, true);


	//Heightmaps
	_meshes["valleyFloor"] = rgl::MeshHelpers::GenerateHeightMap(16, 16, 10, "Assets/Textures/heightmap.png");
}

void AssetPack::loadSpaceResources()
{
	_cubemaps["space_blue"] = rgl::TextureLoader::LoadCubemapFromFile({
		"Assets/Textures/cubemaps/Space/Blue/bkg1_right.png",
		"Assets/Textures/cubemaps/Space/Blue/bkg1_left.png",
		"Assets/Textures/cubemaps/Space/Blue/bkg1_top.png",
		"Assets/Textures/cubemaps/Space/Blue/bkg1_bot.png",
		"Assets/Textures/cubemaps/Space/Blue/bkg1_back.png" ,
		"Assets/Textures/cubemaps/Space/Blue/bkg1_front.png" }, true);

	_cubemaps["space_light_blue"] = rgl::TextureLoader::LoadCubemapFromFile({
		"Assets/Textures/cubemaps/Valley/rusted_west.jpg",
		"Assets/Textures/cubemaps/Valley/rusted_east.jpg",
		"Assets/Textures/cubemaps/Valley/rusted_up.jpg",
		"Assets/Textures/cubemaps/Valley/rusted_down.jpg",
		"Assets/Textures/cubemaps/Valley/rusted_south.jpg" ,
		"Assets/Textures/cubemaps/Valley/rusted_north.jpg" }, true);

	_cubemaps["space_red"] = rgl::TextureLoader::LoadCubemapFromFile({
		"Assets/Textures/cubemaps/Valley/rusted_west.jpg",
		"Assets/Textures/cubemaps/Valley/rusted_east.jpg",
		"Assets/Textures/cubemaps/Valley/rusted_up.jpg",
		"Assets/Textures/cubemaps/Valley/rusted_down.jpg",
		"Assets/Textures/cubemaps/Valley/rusted_south.jpg" ,
		"Assets/Textures/cubemaps/Valley/rusted_north.jpg" }, true);

}

void AssetPack::loadAbductionResources()
{
	////Particles
	//rgl::Shader* fireVertShader = new rgl::Shader("Assets/Shaders/Particles/fireVert.glsl", GL_VERTEX_SHADER);
	//rgl::Shader* fireFragShader = new rgl::Shader("Assets/Shaders/Particles/fireFrag.glsl", GL_FRAGMENT_SHADER);
	//rgl::Shader* fireGeoShader = new rgl::Shader("Assets/Shaders/Particles/fireGeo.glsl", GL_GEOMETRY_SHADER);
}
