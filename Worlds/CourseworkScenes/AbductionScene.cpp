#include "AbductionScene.h"
#include <RobGL/DirectionalLightCamera.h>


AbductionScene::AbductionScene(Window & window, Input & input) : BaseScene(window, input)
{
}

AbductionScene::~AbductionScene()
{
}

void AbductionScene::setupScene(AssetPack * assets)
{
	rgl::Camera* mainCamera = new rgl::Camera;
	_cameraController = new CameraController(mainCamera, &_input);

	_screenInfoUniform = new rgl::ScreenInformationUniform(800, 600);

	_renderer.enablePostProcessing({ assets->getShader("TexturedVertex"), assets->getShader("UnlitTexturedFragment") });
	_renderer.enableDeferredLighting({ assets->getShader("PointLightVertex"), assets->getShader("PointLightFragment") }, { assets->getShader("LightingCombineVertex"), assets->getShader("LightingCombineFragment") }, mainCamera, _screenInfoUniform);
	//_renderer.enableShadowMapping({ assets->getShader("ShadowMapVertex"), assets->getShader("ShadowMapFragment") }, { assets->getShader("AnimatedShadowMapVertex"), assets->getShader("ShadowMapFragment") }, directionalLightCamera, 2160);

	
	mainCamera->setProjectionPerspective(800, 600);

	rgl::DirectionalLightCamera* directionalLightCamera = new rgl::DirectionalLightCamera(glm::vec4(0.25f, 0.25f,0.25f, 1), glm::vec3(0, 1, 0));
	rgl::DirectionalLightUniform* directionalLightUniform = directionalLightCamera->getUniformData();
	directionalLightCamera->setProjectionOrthographic(1, 400, 300, 300);
	directionalLightCamera->setPosition(glm::vec3(75, 200, 100));
	directionalLightCamera->pitch(-3.14f / 2);
	directionalLightCamera->yaw(-3.14f / 2);


	//directionalLightUniform->setShadowTexture(_renderer.getShadowMapTexture());

	//Setup particles
	rgl::ParticleSystem* beamParticles = new rgl::ParticleSystem(10000);
	beamParticles->setTexture(assets->getTexture("particle"));
	beamParticles->setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(75,0,75)) * glm::scale(glm::mat4(1), glm::vec3(5, 1, 5)));

	//Setup render pools
	rgl::ParticlePool*  beamParticlesPool = new rgl::ParticlePool({ assets->getShader("BeamVertexFX"),assets->getShader("BeamGeoFX"), assets->getShader("BeamFragmentFX")}, mainCamera, beamParticles);
	_renderer.addRenderPool(beamParticlesPool);

	rgl::RenderPool* texturedRenderPool = new rgl::RenderPool({ assets->getShader("TexturedVertex"), assets->getShader("TexturedFragment") }, mainCamera);
	texturedRenderPool->addUniformData(directionalLightUniform);
	_renderer.addRenderPool(texturedRenderPool);

	//Setup render objects
	rgl::RenderObject* floor = new rgl::RenderObject;
	floor->setMesh(assets->getMesh("abductionFloor"));
	floor->setTexture(assets->getTexture("ground_rock"));
	floor->setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(0, 0, 0)) * glm::scale(glm::mat4(1), glm::vec3(1, 3, 1)));
	texturedRenderPool->addRenderObject(floor);

	_ufoNode = new rgl::scenes::SceneNode;
	rgl::RenderObject* ufo = new rgl::RenderObject;
	ufo->setMesh(assets->getMesh("ufo"));
	ufo->setTexture(assets->getTexture("ufo"));
	_ufoNode->setPosition(glm::vec3(75, 75, 75));
	_ufoNode->setScale(glm::vec3(1, 1, 1));
	texturedRenderPool->addRenderObject(ufo);
	_ufoNode->attachRenderObject(ufo);

	//Setup lights
	rgl::PointLight* light = new rgl::PointLight(glm::vec4(1, 0, 0, 1));
	light->setMesh(assets->getMesh("sphere"));
	light->setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(50,0,50))*glm::scale(glm::mat4(1),glm::vec3(40,40,40)));
	_renderer.addLight(light);

	rgl::PointLight* light2 = new rgl::PointLight(glm::vec4(1, 1, 0, 1));
	light2->setMesh(assets->getMesh("sphere"));
	light2->setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(80, 10, 50))*glm::scale(glm::mat4(1), glm::vec3(60, 60, 60)));
	_renderer.addLight(light2);

	rgl::PointLight* light3 = new rgl::PointLight(glm::vec4(0, 0, 1, 1));
	light3->setMesh(assets->getMesh("sphere"));
	light3->setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(100, 0, 90))*glm::scale(glm::mat4(1), glm::vec3(40, 40, 40)));
	_renderer.addLight(light3);

	rgl::PointLight* light4 = new rgl::PointLight(glm::vec4(0, 0, 1, 1));
	light4->setMesh(assets->getMesh("sphere"));
	light4->setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(75, 20, 75))*glm::scale(glm::mat4(1), glm::vec3(75, 75, 75)));
	_renderer.addLight(light4);

	rgl::scenes::SceneNode* ufoLightNode1 = new rgl::scenes::SceneNode;
	rgl::PointLight* ufoLight1 = new rgl::PointLight(glm::vec4(0,1, 0, 1));
	ufoLightNode1->setScale(glm::vec3(20,20,20));
	ufoLightNode1->setPosition(glm::vec3(0, -15, 0));
	ufoLightNode1->attachRenderObject(ufoLight1);
	_ufoNode->addChild(ufoLightNode1);
	_renderer.addLight(ufoLight1);


	rgl::SkyboxFX* skybox = new rgl::SkyboxFX({ assets->getShader("SkyboxVertexFX"), assets->getShader("SkyboxFragmentFX") }, assets->getCubemap("abduction"), _renderer.getDepthTexture(), mainCamera);
	_renderer.addPostProcessingFX(skybox);

	_sceneNameText->setText("Alien Abduction");
}


void AbductionScene::draw(float delta)
{
	_cameraController->update(delta);
	_currentUfoRotation += delta * _ufoRotateSpeed;
	_ufoNode->setRotation(glm::rotate(glm::mat4(1), _currentUfoRotation, glm::vec3(0,1,0)));

	BaseScene::draw(delta);
}


