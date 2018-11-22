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
	_shaders["TexturedFragment"] = new rgl::Shader("Assets/Shaders/litTexFrag.glsl", GL_FRAGMENT_SHADER);
	_shaders["UnlitTexturedFragment"] = new rgl::Shader("Assets/Shaders/texFrag.glsl", GL_FRAGMENT_SHADER);

	_shaders["AnimatedVertex"] = new rgl::Shader("Assets/Shaders/animatedVert.glsl", GL_VERTEX_SHADER);

	_shaders["TexturedVertex_NO_MVP"] = new rgl::Shader("Assets/Shaders/texVertNoMVP.glsl", GL_VERTEX_SHADER);

	//Lighting
	_shaders["PointLightVertex"] = new rgl::Shader("Assets/Shaders/pointLightVert.glsl", GL_VERTEX_SHADER);
	_shaders["PointLightFragment"] = new rgl::Shader("Assets/Shaders/pointLightFrag.glsl", GL_FRAGMENT_SHADER);

	_shaders["AnimatedShadowMapVertex"] = new rgl::Shader("Assets/Shaders/animatedShadowMapVert.glsl", GL_VERTEX_SHADER);
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

	_shaders["RenderFBOFragmentFX"] = new rgl::Shader("Assets/Shaders/renderFBOFragFX.glsl", GL_FRAGMENT_SHADER);
	_shaders["RenderDepthFBOFragmentFX"] = new rgl::Shader("Assets/Shaders/renderDepthFBOFragFX.glsl", GL_FRAGMENT_SHADER);

	//### Models ###//
	_meshes["triangle"] = rgl::MeshHelpers::GenerateTriangle();
	_meshes["quad"] = rgl::MeshHelpers::GenerateQuad();
	_meshes["anky"] = rgl::MeshHelpers::LoadMeshFromGLTF("Assets/Models/anky.gltf");
	_meshes["sphere"] = rgl::MeshHelpers::LoadMeshFromObj("Assets/Models/ico.obj");


	//Animated Meshes
	_animatedMeshes["anky"] = rgl::MeshHelpers::LoadAnimatedMeshFromGLTF("Assets/Models/anky.gltf");

	//### Textures ###//
	_textures["box"] = rgl::TextureLoader::LoadFromFile("Assets/Textures/test.png", false, true);
	_textures["stainedglass"] = rgl::TextureLoader::LoadFromFile("Assets/Textures/stainedglass.tga", true, true);
	_textures["anky"] = rgl::TextureLoader::LoadFromFile("Assets/Textures/Anky.png", true, true);
	_textures["particle"] = rgl::TextureLoader::LoadFromFile("Assets/Textures/particle.tga", true, false);
	_textures["water"] = rgl::TextureLoader::LoadFromFile("Assets/Textures/water.jpg", false, true);

	//### Text ###//
	_alphabet = new rgl::Text("Assets/Fonts/arial.ttf");

}

void AssetPack::loadValleyResources()
{
	//Shaders
	_shaders["ValleyFloorFragment"] = new rgl::Shader("Assets/Shaders/Valley/valleyFloorFrag.glsl", GL_FRAGMENT_SHADER);
	_shaders["WaterFragment"] = new rgl::Shader("Assets/Shaders/Valley/waterFrag.glsl", GL_FRAGMENT_SHADER);
	_shaders["WaterVertex"] = new rgl::Shader("Assets/Shaders/Valley/waterVert.glsl", GL_VERTEX_SHADER);
	_shaders["WaterTessControl"] = new rgl::Shader("Assets/Shaders/Valley/waterTessControl.glsl", GL_TESS_CONTROL_SHADER);
	_shaders["WaterTessEvaluation"] = new rgl::Shader("Assets/Shaders/Valley/waterTessEval.glsl", GL_TESS_EVALUATION_SHADER);

	//Skybox
	_cubemaps["valley"] = rgl::TextureLoader::LoadCubemapFromFile({
		"Assets/Textures/cubemaps/Valley/rusted_west.jpg",
		"Assets/Textures/cubemaps/Valley/rusted_east.jpg",
		"Assets/Textures/cubemaps/Valley/rusted_up.jpg",
		"Assets/Textures/cubemaps/Valley/rusted_down.jpg",
		"Assets/Textures/cubemaps/Valley/rusted_south.jpg" ,
		"Assets/Textures/cubemaps/Valley/rusted_north.jpg" }, true);

	//Textures
	_textures["ground_rock"] = rgl::TextureLoader::LoadFromFile("Assets/Textures/ground_rock.jpg", false, true);
	_textures["ground_grass"] = rgl::TextureLoader::LoadFromFile("Assets/Textures/ground_grass.png", false, true);
	_textures["ground_sand"] = rgl::TextureLoader::LoadFromFile("Assets/Textures/ground_sand.jpg", false, true);

	//Heightmaps
	_meshes["valleyFloor_1"] = rgl::MeshHelpers::GenerateHeightMap(16, 16, 10, "Assets/Textures/heightmaps/valley_1.png");
	_meshes["valleyFloor_2"] = rgl::MeshHelpers::GenerateHeightMap(16, 16, 10, "Assets/Textures/heightmaps/valley_2.png");
	_meshes["valleyFloor_3"] = rgl::MeshHelpers::GenerateHeightMap(16, 16, 10, "Assets/Textures/heightmaps/valley_3.png");
	_meshes["valleyFloor_4"] = rgl::MeshHelpers::GenerateHeightMap(16, 16, 10, "Assets/Textures/heightmaps/valley_4.png");

	_meshes["water"] = rgl::MeshHelpers::GenerateHeightMap(16, 16, 10);
	_meshes["water"]->setType(GL_PATCHES);

	//Hats
	_meshes["cowboyHat"] = rgl::MeshHelpers::LoadMeshFromObj("Assets/Models/Valley/hat1.obj");
	_textures["cowboyHat"] = rgl::TextureLoader::LoadFromFile("Assets/Textures/Valley/CowboyHat.png", true, true);

	_meshes["topHat"] = rgl::MeshHelpers::LoadMeshFromObj("Assets/Models/Valley/topHat.obj");
	_textures["topHat"] = rgl::TextureLoader::LoadFromFile("Assets/Textures/Valley/TopHat.png", true, true);

	_meshes["bowlerHat"] = rgl::MeshHelpers::LoadMeshFromObj("Assets/Models/Valley/bowlerHat.obj");
	_textures["bowlerHat"] = rgl::TextureLoader::LoadFromFile("Assets/Textures/Valley/BowlerHat.jpg", false, true);
}

void AssetPack::loadSpaceResources()
{
	_cubemaps["space_blue"] = rgl::TextureLoader::LoadCubemapFromFile({
		"Assets/Textures/cubemaps/Space/Blue/bkg1_right.png",
		"Assets/Textures/cubemaps/Space/Blue/bkg1_left.png",
		"Assets/Textures/cubemaps/Space/Blue/bkg1_top.png",
		"Assets/Textures/cubemaps/Space/Blue/bkg1_bot.png",
		"Assets/Textures/cubemaps/Space/Blue/bkg1_front.png" ,
		"Assets/Textures/cubemaps/Space/Blue/bkg1_back.png" }, true);

	_cubemaps["space_light_blue"] = rgl::TextureLoader::LoadCubemapFromFile({
		"Assets/Textures/cubemaps/Space/LightBlue/right.png",
		"Assets/Textures/cubemaps/Space/LightBlue/left.png",
		"Assets/Textures/cubemaps/Space/LightBlue/top.png",
		"Assets/Textures/cubemaps/Space/LightBlue/bot.png",
		"Assets/Textures/cubemaps/Space/LightBlue/front.png" ,
		"Assets/Textures/cubemaps/Space/LightBlue/back.png" }, true);

	_cubemaps["space_red"] = rgl::TextureLoader::LoadCubemapFromFile({
		"Assets/Textures/cubemaps/Space/Red/bkg1_right1.png",
		"Assets/Textures/cubemaps/Space/Red/bkg1_left2.png",
		"Assets/Textures/cubemaps/Space/Red/bkg1_top3.png",
		"Assets/Textures/cubemaps/Space/Red/bkg1_bottom4.png",
		"Assets/Textures/cubemaps/Space/Red/bkg1_front5.png" ,
		"Assets/Textures/cubemaps/Space/Red/bkg1_back6.png" }, true);

	_shaders["SpaceSkyboxFragmentFX"] = new rgl::Shader("Assets/Shaders/Space/spaceSkyboxFragFX.glsl", GL_FRAGMENT_SHADER);

	//Models
	//_meshes["Earth"] = rgl::MeshHelpers::LoadMeshFromGLTF("Assets/Models/Space/Earth/scene.gltf");
	_meshes["Planet"] = rgl::MeshHelpers::LoadMeshFromGLTF("Assets/Models/Space/sphere.gltf");

	//Textures
	_textures["Earth"] = rgl::TextureLoader::LoadFromFile("Assets/Textures/Space/Earth/earth.jpg",false,true);
	_textures["Earth_Atmosphere"] = rgl::TextureLoader::LoadFromFile("Assets/Textures/Space/Earth/atmosphere.png", true, true);
	_textures["Moon"] = rgl::TextureLoader::LoadFromFile("Assets/Textures/Space/Earth/moon.jpg", false, true);
	_textures["Sun"] = rgl::TextureLoader::LoadFromFile("Assets/Textures/Space/Sun/sun.jpg", false, true);
}

void AssetPack::loadAbductionResources()
{
	////Particles
	_shaders["BeamVertexFX"] = new rgl::Shader("Assets/Shaders/Particles/fireVert.glsl", GL_VERTEX_SHADER);
	_shaders["BeamFragmentFX"] = new rgl::Shader("Assets/Shaders/Particles/fireFrag.glsl", GL_FRAGMENT_SHADER);
	_shaders["BeamGeoFX"] = new rgl::Shader("Assets/Shaders/Particles/fireGeo.glsl", GL_GEOMETRY_SHADER);


	//Skybox
	_cubemaps["abduction"] = rgl::TextureLoader::LoadCubemapFromFile({
		"Assets/Textures/cubemaps/Abduction/mnight_rt.tga" ,
		"Assets/Textures/cubemaps/Abduction/mnight_lf.tga" ,
		"Assets/Textures/cubemaps/Abduction/mnight_up.tga" ,
		"Assets/Textures/cubemaps/Abduction/mnight_dn.tga" ,
		"Assets/Textures/cubemaps/Abduction/mnight_ft.tga"  ,
		"Assets/Textures/cubemaps/Abduction/mnight_bk.tga" }, true);

	_meshes["abductionFloor"] = rgl::MeshHelpers::GenerateHeightMap(16, 16, 10, "Assets/Textures/heightmaps/abduction.png");

	//Textures
	_textures["ufo"] = rgl::TextureLoader::LoadFromFile("Assets/Textures/Abduction/ufo_diffuse.png", true, true);


	//Meshes
	_meshes["ufo"] = rgl::MeshHelpers::LoadMeshFromObj("Assets/Models/Abduction/ufo2.obj");
}

rgl::Shader * AssetPack::getShader(std::string s)
{
	return _shaders[s];
}

rgl::Texture * AssetPack::getTexture(std::string t)
{
	return _textures[t];
}

rgl::Cubemap * AssetPack::getCubemap(std::string c)
{
	return _cubemaps[c];
}

rgl::Mesh * AssetPack::getMesh(std::string m)
{
	return _meshes[m];
}

rgl::AnimatedMesh * AssetPack::getAnimatedMesh(std::string m)
{
	return _animatedMeshes[m];
}

rgl::Text * AssetPack::getText()
{
	return _alphabet;
}

