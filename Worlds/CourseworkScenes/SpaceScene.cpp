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
	_mainCamera = new rgl::Camera;
	_cameraController = new CameraController(_mainCamera, &_input);

	_mainCamera->setPosition(glm::vec3(10, 0, 40));
	_renderer.enablePostProcessing({ assets->getShader("TexturedVertex"), assets->getShader("UnlitTexturedFragment") });

	_mainCamera->setProjectionPerspective(800,600);

	//Setup render pools
	rgl::RenderPool* opaqueRenderPool = new rgl::RenderPool({ assets->getShader("TexturedVertex"), assets->getShader("TexturedFragment") }, _mainCamera);
	_renderer.addRenderPool(opaqueRenderPool);

	rgl::RenderPool* transparentRenderPool = new rgl::RenderPool({ assets->getShader("TexturedVertex"), assets->getShader("TexturedFragment") }, _mainCamera);
	_renderer.addRenderPool(transparentRenderPool);

	rgl::SkyboxFX* skybox = new rgl::SkyboxFX({ assets->getShader("SkyboxVertexFX"), assets->getShader("SpaceSkyboxFragmentFX") }, assets->getCubemap("space_blue"), _renderer.getDepthTexture(), _mainCamera);

	_skyboxUniform = new LerpSkyboxUniform(assets->getCubemap("space_light_blue"), assets->getCubemap("space_red"), 20);
	skybox->addUniformData(_skyboxUniform);

	_renderer.addPostProcessingFX(skybox);

	//Setup scene nodes and render objects
	//Sun
	_sunNode = new rgl::scenes::SceneNode;
	rgl::RenderObject* sunRO = new rgl::RenderObject;
	sunRO->setMesh(assets->getMesh("Planet"));
	sunRO->setTexture(assets->getTexture("Sun"));
	opaqueRenderPool->addRenderObject(sunRO);
	_sunNode->attachRenderObject(sunRO);
	_sunNode->setScale(glm::vec3(10.0f, 10.0f, 10.0f));
	_sunNode->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	//Mercury
	_mercuryNode = new rgl::scenes::SceneNode;
	rgl::RenderObject* mercuryRO = new rgl::RenderObject;
	mercuryRO->setMesh(assets->getMesh("Planet"));
	mercuryRO->setTexture(assets->getTexture("Mercury"));
	opaqueRenderPool->addRenderObject(mercuryRO);
	_mercuryNode->attachRenderObject(mercuryRO);
	_mercuryNode->setScale(glm::vec3(0.1f, 0.1f, 0.1f));
	_mercuryNode->setPosition(glm::vec3(5.0f, 0.0f, 0.0f));
	_sunNode->addChild(_mercuryNode);

	//Earth
	_earthNode = new rgl::scenes::SceneNode;
	rgl::RenderObject* earthRO = new rgl::RenderObject;
	earthRO->setMesh(assets->getMesh("Planet"));
	earthRO->setTexture(assets->getTexture("Earth"));
	opaqueRenderPool->addRenderObject(earthRO);
	_earthNode->attachRenderObject(earthRO);
	_earthNode->setScale(glm::vec3(0.2f, 0.2f, 0.2f));
	_earthNode->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	_sunNode->addChild(_earthNode);

	_earthAtmosphereNode = new rgl::scenes::SceneNode;
	rgl::RenderObject* earthAtmosphereRO = new rgl::RenderObject;
	earthAtmosphereRO->setMesh(assets->getMesh("Planet"));
	earthAtmosphereRO->setTexture(assets->getTexture("Earth_Atmosphere"));
	transparentRenderPool->addRenderObject(earthAtmosphereRO);
	_earthAtmosphereNode->attachRenderObject(earthAtmosphereRO);
	_earthAtmosphereNode->setScale(glm::vec3(1.1f, 1.1f, 1.1f));
	_earthNode->addChild(_earthAtmosphereNode);

	_ufoNode = new rgl::scenes::SceneNode;
	rgl::RenderObject* ufoRO = new rgl::RenderObject;
	ufoRO->setMesh(assets->getMesh("ufo"));
	ufoRO->setTexture(assets->getTexture("ufo"));
	opaqueRenderPool->addRenderObject(ufoRO);
	_ufoNode->attachRenderObject(ufoRO);
	_ufoNode->setScale(glm::vec3(0.01f, 0.01f, 0.01f));
	_ufoNode->setPosition(glm::vec3(0, 1.5f, 0));
	_earthNode->addChild(_ufoNode);

	_moonNode = new rgl::scenes::SceneNode;
	rgl::RenderObject* moonRO = new rgl::RenderObject;
	moonRO->setMesh(assets->getMesh("Planet"));
	moonRO->setTexture(assets->getTexture("Moon"));
	opaqueRenderPool->addRenderObject(moonRO);
	_moonNode->attachRenderObject(moonRO);
	_moonNode->setScale(glm::vec3(0.25f, 0.25f, 0.25f));
	_moonNode->setPosition(glm::vec3(1.0f, 0.0f, _moonOrbitRadius));
	_earthNode->addChild(_moonNode);

	_moonMoonNode = new rgl::scenes::SceneNode;
	rgl::RenderObject* moonMoonRO = new rgl::RenderObject;
	moonMoonRO->setMesh(assets->getMesh("Planet"));
	moonMoonRO->setTexture(assets->getTexture("Europa"));
	opaqueRenderPool->addRenderObject(moonMoonRO);
	_moonMoonNode->attachRenderObject(moonMoonRO);
	_moonMoonNode->setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	_moonMoonNode->setPosition(glm::vec3(1.0f, 0.0f, _moonOrbitRadius));
	_moonNode->addChild(_moonMoonNode);

	//Jupiter
	_jupiterNode = new rgl::scenes::SceneNode;
	rgl::RenderObject* jupiterRO = new rgl::RenderObject;
	jupiterRO->setMesh(assets->getMesh("Planet"));
	jupiterRO->setTexture(assets->getTexture("Jupiter"));
	opaqueRenderPool->addRenderObject(jupiterRO);
	_jupiterNode->attachRenderObject(jupiterRO);
	_jupiterNode->setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	_jupiterNode->setPosition(glm::vec3(10.0f, 0.0f, 0.0f));
	_sunNode->addChild(_jupiterNode);

	_jupiterMoonNode = new rgl::scenes::SceneNode;
	rgl::RenderObject* jupiterMoonRO = new rgl::RenderObject;
	jupiterMoonRO->setMesh(assets->getMesh("Planet"));
	jupiterMoonRO->setTexture(assets->getTexture("Moon"));
	opaqueRenderPool->addRenderObject(jupiterMoonRO);
	_jupiterMoonNode->attachRenderObject(jupiterMoonRO);
	_jupiterMoonNode->setScale(glm::vec3(0.2f, 0.2f, 0.2f));
	_jupiterMoonNode->setPosition(glm::vec3(1.0f, 0.0f, 0.0f));
	_jupiterNode->addChild(_jupiterMoonNode);

	//Saturn
	_saturnNode = new rgl::scenes::SceneNode;
	rgl::RenderObject* saturnRO = new rgl::RenderObject;
	saturnRO->setMesh(assets->getMesh("Planet"));
	saturnRO->setTexture(assets->getTexture("Saturn"));
	opaqueRenderPool->addRenderObject(saturnRO);
	_saturnNode->attachRenderObject(saturnRO);
	_saturnNode->setScale(glm::vec3(0.7f, 0.7f, 0.7f));
	_saturnNode->setPosition(glm::vec3(15.0f, 0.0f, 0.0f));
	_sunNode->addChild(_saturnNode);

	_sceneNameText->setText("Spaaaacccceee");
}



void SpaceScene::draw(float delta)
{
	_cameraController->update(delta * 5);
	_skyboxUniform->update(delta);

	_earthAtmosphereRotateAmount += _earthAtmosphereRotateSpeed * delta;
	_earthAtmosphereNode->setRotation(glm::rotate(glm::mat4(1), _earthAtmosphereRotateAmount, glm::vec3(0,1,0)));
	_ufoNode->setRotation(glm::rotate(glm::mat4(1), -_earthAtmosphereRotateAmount, glm::vec3(0, 1, 0)));

	_currentMoonOrbit += _moonOrbitSpeed * delta;
	_moonNode->setPosition(calculateOrbit(_currentMoonOrbit,_moonOrbitRadius));
	_moonMoonNode->setPosition(calculateOrbit(-_currentMoonOrbit, _moonOrbitRadius));

	_currentMercuryOrbit += _mercuryOrbitSpeed * delta;
	_mercuryNode->setPosition(calculateOrbit(_currentMercuryOrbit, _mercuryOrbitRadius));

	_currentSaturnOrbit += _saturnOrbitSpeed * delta;
	_saturnNode->setPosition(calculateOrbit(_currentSaturnOrbit, _saturnOrbitRadius));

	_currentJupiterOrbit += _jupiterOrbitSpeed * delta;
	_jupiterNode->setPosition(calculateOrbit(_currentJupiterOrbit, _jupiterOrbitRadius));

	_currentJupiterMoonOrbit += _jupiterMoonOrbitSpeed * delta;
	_jupiterMoonNode->setPosition(calculateOrbit(_currentJupiterMoonOrbit, _jupiterMoonOrbitRadius));

	_currentEarthOrbit += _earthOrbitSpeed * delta;
	_earthNode->setPosition(calculateOrbit(_currentEarthOrbit, _earthOrbitRadius));

	if (_input.isKeyPressed(InputButton::KEYBOARD_E)) {
		_lockToEarth = !_lockToEarth;
	}

	if (_lockToEarth) {
		_mainCamera->setPosition(_earthNode->getWorldPosition() + glm::vec3(0,0,18));
	}

	BaseScene::draw(delta);
}
