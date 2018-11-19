#include "ValleyScene.h"

#include <RobGL/SkyboxFX.h>
#include <RobGL/DirectionalLightCamera.h>
#include <RobGL/AdditionalTextureUniform.h>

#include "Random.h"

ValleyScene::ValleyScene(Window& window, Input& i) : BaseScene(window, i)
{
}

ValleyScene::~ValleyScene()
{
}

void ValleyScene::setupScene(AssetPack * assets)
{
	//Setup camera
	rgl::Camera* mainCamera = new rgl::Camera;
	_cameraController = new CameraController(mainCamera, &_input);
	mainCamera->setProjectionPerspective(800,600);
	mainCamera->setPosition(glm::vec3(0, 0, -10));

	//Setup renderer
	_renderer.enablePostProcessing({ assets->getShader("TexturedVertex"), assets->getShader("UnlitTexturedFragment") });

	rgl::DirectionalLightCamera* directionalLightCamera = new rgl::DirectionalLightCamera(glm::vec4(1, 1, 1, 1), glm::vec3(1, 1, -1));
	rgl::DirectionalLightUniform* directionalLightUniform = directionalLightCamera->getUniformData();
	directionalLightCamera->setProjectionOrthographic(1, 100, 100, 100);
	directionalLightCamera->setPosition(glm::vec3(40, 40, 40));
	directionalLightCamera->pitch(-3.14 / 3);

	rgl::ScreenInformationUniform*  screenInfoUniform = new rgl::ScreenInformationUniform(800, 600);

	_renderer.enableDeferredLighting({ assets->getShader("PointLightVertex"), assets->getShader("PointLightFragment") }, { assets->getShader("LightingCombineVertex"), assets->getShader("LightingCombineFragment") }, mainCamera, screenInfoUniform);
	_renderer.enableShadowMapping({assets->getShader("ShadowMapVertex"), assets->getShader("ShadowMapFragment")}, directionalLightCamera, 2160);

	directionalLightUniform->setShadowTexture(_renderer.getShadowMapTexture());


	//Setup render pools
	rgl::RenderPool* valleyRenderPool = new rgl::RenderPool({ assets->getShader("TexturedVertex"), assets->getShader("ValleyFloorFragment") }, mainCamera);
	rgl::AdditionalTextureUniform* textureUniform = new rgl::AdditionalTextureUniform(assets->getTexture("ground_sand"), "flatTex");
	valleyRenderPool->addUniformData(directionalLightUniform);
	valleyRenderPool->addUniformData(textureUniform);
	_renderer.addRenderPool(valleyRenderPool);

	rgl::RenderPool* dinosaurRenderPool = new rgl::RenderPool({ assets->getShader("AnimatedVertex"), assets->getShader("TexturedFragment") }, mainCamera);
	dinosaurRenderPool->addUniformData(directionalLightUniform);
	_renderer.addRenderPool(dinosaurRenderPool);

	//Setup render objects
	rgl::RenderObject* valleyFloor = new rgl::RenderObject;
	valleyFloor->setMesh(assets->getMesh("valleyFloor_1"));
	valleyFloor->setTexture(assets->getTexture("ground_rock"));
	valleyFloor->setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(0, 0, 0)) * glm::scale(glm::mat4(1), glm::vec3(1,5,1)));
	valleyRenderPool->addRenderObject(valleyFloor);
	//_renderer.addRenderObjectToShadowPool(valleyFloor);

	rgl::RenderObject* valleyFloor2 = new rgl::RenderObject;
	valleyFloor2->setMesh(assets->getMesh("valleyFloor_2"));
	valleyFloor2->setTexture(assets->getTexture("ground_rock"));
	valleyFloor2->setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(0, 0, 150)) * glm::scale(glm::mat4(1), glm::vec3(1, 5, 1)));
	valleyRenderPool->addRenderObject(valleyFloor2);
	//_renderer.addRenderObjectToShadowPool(valleyFloor2);

	//Setup dinosaurs
	for (int i = 0; i < NUMBER_OF_DINOS; ++i) {
		rgl::AnimatedRenderObject* dino = new rgl::AnimatedRenderObject;
		dino->setMesh(assets->getAnimatedMesh("anky"));
		dino->setTexture(assets->getTexture("anky"));
		dino->setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(15 * i + Random::random() * 3, -3, i + 70 + 10*Random::random())) * glm::scale(glm::mat4(1), glm::vec3(1, 1, 1)) * glm::rotate(glm::mat4(1), -glm::half_pi<float>(), glm::vec3(0, 1, 0)));
		
		//Randomly displace the animation
		dino->setActiveAnimation(0, Random::random() * 2);
		_dinos.push_back(dino);
		dinosaurRenderPool->addRenderObject(dino);
	}

	//Setup post processing
	rgl::SkyboxFX* skybox = new rgl::SkyboxFX({assets->getShader("SkyboxVertexFX"), assets->getShader("SkyboxFragmentFX") },assets->getCubemap("valley"),_renderer.getDepthTexture(), mainCamera);

	_fpsText = new rgl::UITextFX({ assets->getShader("TextVertex"), assets->getShader("TextFragment") }, assets->getText());
	_fpsText->setColour(glm::vec4(1,1,1,1));
	_fpsText->setPosition(0.5f, 0.75f);
	_fpsText->setScale(0.1f);
	_fpsText->setText("FPS: 1234");

	_sceneNameText = new rgl::UITextFX({ assets->getShader("TextVertex"), assets->getShader("TextFragment") }, assets->getText());
	_sceneNameText->setColour(glm::vec4(1, 1, 1, 1));
	_sceneNameText->setPosition(0.25f, -0.5f);
	_sceneNameText->setScale(0.1f);
	_sceneNameText->setText("Dinosaur Valley");


	_renderer.addPostProcessingFX(skybox);
	_renderer.addPostProcessingFX(_fpsText);
	_renderer.addPostProcessingFX(_sceneNameText);
}

void ValleyScene::draw(float delta)
{
	_cameraController->update(delta);

	//Update framerate
	_seconds += delta;
	_frames++;
	if (_seconds > 1) {
		_seconds = 0;

		_fpsText->setText("FPS: " + std::to_string(_frames));
		_frames = 0;
	}

	updateDinos(delta);

	BaseScene::draw(delta);
}

void ValleyScene::updateDinos(float delta)
{
	for (auto& d : _dinos) {

		auto currentMatrix = d->getModelMatrix();

		if (currentMatrix[3].x < 0) {
			d->setModelMatrix(currentMatrix * glm::translate(glm::mat4(1), glm::vec3(0, 0, -150)));
		}
		else {
			d->setModelMatrix(currentMatrix * glm::translate(glm::mat4(1), glm::vec3(0, 0, DINO_SPEED*delta)));
		}

		

		

	}
}
