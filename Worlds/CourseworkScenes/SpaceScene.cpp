#include "SpaceScene.h"
#include <RobGL/SkyboxFX.h>

SpaceScene::SpaceScene(Window & window, Input& input) : BaseScene(window, input)
{
}

SpaceScene::~SpaceScene()
{
}

void SpaceScene::setupScene(AssetPack * assets)
{
	rgl::Camera* mainCamera = new rgl::Camera;
	_cameraController = new CameraController(mainCamera, &_input);

	_renderer.enablePostProcessing({ assets->getShader("TexturedVertex"), assets->getShader("UnlitTexturedFragment") });

	mainCamera->setProjectionPerspective(800,600);

	//Setup render pools
	rgl::RenderPool* opaqueRenderPool = new rgl::RenderPool({ assets->getShader("TexturedVertex"), assets->getShader("TexturedFragment") }, mainCamera);
	_renderer.addRenderPool(opaqueRenderPool);

	rgl::RenderPool* transparentRenderPool = new rgl::RenderPool({ assets->getShader("TexturedVertex"), assets->getShader("TexturedFragment") }, mainCamera);
	_renderer.addRenderPool(transparentRenderPool);

	rgl::SkyboxFX* skybox = new rgl::SkyboxFX({ assets->getShader("SkyboxVertexFX"), assets->getShader("SpaceSkyboxFragmentFX") }, assets->getCubemap("space_blue"), _renderer.getDepthTexture(), mainCamera);

	_skyboxUniform = new LerpSkyboxUniform(assets->getCubemap("space_light_blue"), assets->getCubemap("space_red"), 20);
	skybox->addUniformData(_skyboxUniform);

	_renderer.setSkybox(skybox);

	//Setup scene nodes and render objects
	rgl::scenes::SceneNode* _earthNode = new rgl::scenes::SceneNode;
	rgl::RenderObject* earthRO = new rgl::RenderObject;
	earthRO->setMesh(assets->getMesh("Planet"));
	earthRO->setTexture(assets->getTexture("Earth"));
	opaqueRenderPool->addRenderObject(earthRO);
	_earthNode->attachRenderObject(earthRO);
	_earthNode->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	_earthNode->setPosition(glm::vec3(1.0f, 1.0f, 1.0f));

	_earthAtmosphereNode = new rgl::scenes::SceneNode;
	rgl::RenderObject* earthAtmosphereRO = new rgl::RenderObject;
	earthAtmosphereRO->setMesh(assets->getMesh("Planet"));
	earthAtmosphereRO->setTexture(assets->getTexture("Earth_Atmosphere"));
	transparentRenderPool->addRenderObject(earthAtmosphereRO);
	_earthAtmosphereNode->attachRenderObject(earthAtmosphereRO);
	_earthAtmosphereNode->setScale(glm::vec3(1.1f, 1.1f, 1.1f));
	_earthNode->addChild(_earthAtmosphereNode);

	_moonNode = new rgl::scenes::SceneNode;
	rgl::RenderObject* moonRO = new rgl::RenderObject;
	moonRO->setMesh(assets->getMesh("Planet"));
	moonRO->setTexture(assets->getTexture("Moon"));
	opaqueRenderPool->addRenderObject(moonRO);
	_moonNode->attachRenderObject(moonRO);
	_moonNode->setScale(glm::vec3(0.25f, 0.25f, 0.25f));
	_moonNode->setPosition(glm::vec3(1.0f, 0.0f, _moonOrbitRadius));
	_earthNode->addChild(_moonNode);

	_sceneNameText->setText("Spaaaacccceee");
}



void SpaceScene::draw(float delta)
{
	_cameraController->update(delta);
	_skyboxUniform->update(delta);

	_earthAtmosphereRotateAmount += _earthAtmosphereRotateSpeed * delta;
	_earthAtmosphereNode->setRotation(glm::rotate(glm::mat4(1), _earthAtmosphereRotateAmount, glm::vec3(0,1,0)));
	
	_currentMoonOrbit += _moonOrbitSpeed * delta;
	_moonNode->setPosition(calculateOrbit(_currentMoonOrbit,_moonOrbitRadius));

	BaseScene::draw(delta);
}
