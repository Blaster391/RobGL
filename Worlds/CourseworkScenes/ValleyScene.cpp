#include "ValleyScene.h"


#include "Random.h"

ValleyScene::ValleyScene(Window& window, Input& i) : BaseScene(window, i)
{
}

ValleyScene::~ValleyScene()
{
	for (auto& a:  _animatedObjects) {
		delete a;
	}
}

void ValleyScene::setupScene(AssetPack * assets)
{
	//Setup camera
	_mainCamera = new rgl::Camera;
	_cameraController = new CameraController(_mainCamera, &_input);
	_mainCamera->setProjectionPerspective(800,600);
	_mainCamera->setPosition(glm::vec3(30, 7, 75));
	_mainCamera->pitch(-0.3f);
	_mainCamera->yaw(-glm::half_pi<float>());

	//Setup renderer
	_renderer.enablePostProcessing({ assets->getShader("TexturedVertex"), assets->getShader("UnlitTexturedFragment") });

	rgl::DirectionalLightCamera* directionalLightCamera = new rgl::DirectionalLightCamera(glm::vec4(1, 1, 1, 1), glm::vec3(1, 1, -1));
	rgl::DirectionalLightUniform* directionalLightUniform = directionalLightCamera->getUniformData();
	directionalLightCamera->setProjectionOrthographic(100, 400, 250, 250);
	directionalLightCamera->setPosition(glm::vec3(200, 200, -20));
	directionalLightCamera->pitch(-0.6f);
	directionalLightCamera->yaw(-3.9f);

	_renderer.enableDeferredLighting({ assets->getShader("PointLightVertex"), assets->getShader("PointLightFragment") }, { assets->getShader("LightingCombineVertex"), assets->getShader("LightingCombineFragment") }, _mainCamera, _screenInfoUniform);
	_renderer.enableShadowMapping({assets->getShader("ShadowMapVertex"), assets->getShader("ShadowMapFragment")}, { assets->getShader("AnimatedShadowMapVertex"), assets->getShader("ShadowMapFragment") }, directionalLightCamera, 2160 * 4);

	directionalLightUniform->setShadowTexture(_renderer.getShadowMapTexture());

	//Setup render pools
	int outerTes[4] = { 10,10,10,10 };
	_tesselationUniform = new rgl::TesselationControlUniform(outerTes, 10);


	rgl::AdditionalTextureUniform* textureUniform = new rgl::AdditionalTextureUniform(assets->getTexture("ground_sand"), "flatTex");
	rgl::RenderPool* valleyRenderPool = new rgl::RenderPool({ assets->getShader("TexturedVertex"), assets->getShader("ValleyFloorFragment") }, _mainCamera);
	valleyRenderPool->addUniformData(directionalLightUniform);
	valleyRenderPool->addUniformData(textureUniform);

	_renderer.addRenderPool(valleyRenderPool);

	rgl::RenderPool* dinosaurRenderPool = new rgl::RenderPool({ assets->getShader("AnimatedVertex"), assets->getShader("TexturedFragment") }, _mainCamera);
	dinosaurRenderPool->addUniformData(directionalLightUniform);
	_renderer.addRenderPool(dinosaurRenderPool);

	rgl::RenderPool* hatRenderPool = new rgl::RenderPool({ assets->getShader("TexturedVertex"), assets->getShader("TexturedFragment") }, _mainCamera);
	hatRenderPool->addUniformData(directionalLightUniform);
	_renderer.addRenderPool(hatRenderPool);

	_waterUniform = new rgl::WaterUniform(assets->getCubemap("valley"));
	rgl::RenderPool* waterRenderPool = new rgl::RenderPool({ assets->getShader("WaterVertex"), assets->getShader("WaterTessControl"), assets->getShader("WaterTessEvaluation"), assets->getShader("WaterFragment") }, _mainCamera);
	waterRenderPool->addUniformData(directionalLightUniform);
	waterRenderPool->addUniformData(_tesselationUniform);
	waterRenderPool->addUniformData(_waterUniform);
	_renderer.addRenderPool(waterRenderPool);

	//Setup render objects
	rgl::RenderObject* valleyFloor = new rgl::RenderObject;
	valleyFloor->setMesh(assets->getMesh("valleyFloor_1"));
	valleyFloor->setTexture(assets->getTexture("ground_rock"));
	valleyFloor->setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(0, 0, 0)) * glm::scale(glm::mat4(1), glm::vec3(1,5,1)));
	valleyRenderPool->addRenderObject(valleyFloor);

	rgl::RenderObject* valleyFloor2 = new rgl::RenderObject;
	valleyFloor2->setMesh(assets->getMesh("valleyFloor_2"));
	valleyFloor2->setTexture(assets->getTexture("ground_rock"));
	valleyFloor2->setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(0, 0, 150)) * glm::scale(glm::mat4(1), glm::vec3(1, 5, 1)));
	valleyRenderPool->addRenderObject(valleyFloor2);

	rgl::RenderObject* valleyFloor3 = new rgl::RenderObject;
	valleyFloor3->setMesh(assets->getMesh("valleyFloor_3"));
	valleyFloor3->setTexture(assets->getTexture("ground_rock"));
	valleyFloor3->setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(-150, 0, 0)) * glm::scale(glm::mat4(1), glm::vec3(1, 5, 1)));
	valleyRenderPool->addRenderObject(valleyFloor3);

	rgl::RenderObject* valleyFloor4 = new rgl::RenderObject;
	valleyFloor4->setMesh(assets->getMesh("valleyFloor_4"));
	valleyFloor4->setTexture(assets->getTexture("ground_rock"));
	valleyFloor4->setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(150, 0, 0)) * glm::scale(glm::mat4(1), glm::vec3(1, 5, 1)));
	valleyRenderPool->addRenderObject(valleyFloor4);

	rgl::RenderObject* water = new rgl::RenderObject;
	water->setMesh(assets->getMesh("water"));
	water->setTexture(assets->getTexture("water"));
	water->setModelMatrix( glm::translate(glm::mat4(1), glm::vec3(15, 13, 185)) * glm::scale(glm::mat4(1), glm::vec3(0.7, 1, 0.7)));
	waterRenderPool->addRenderObject(water);

	//Setup dinosaurs
	//Drinking dinos
	rgl::AnimatedRenderObject* drinkingDino1 = new rgl::AnimatedRenderObject;
	drinkingDino1->setMesh(assets->getAnimatedMesh("anky"));
	drinkingDino1->setTexture(assets->getTexture("anky"));
	drinkingDino1->setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(82, 13.0f, 203.5f)) * glm::scale(glm::mat4(1), glm::vec3(1, 1, 1)) * glm::rotate(glm::mat4(1), -1.4f, glm::vec3(0, 1, 0))* glm::rotate(glm::mat4(1), 0.2f, glm::vec3(1, 0, 0)));
	//Randomly displace the animation
	drinkingDino1->setActiveAnimation(1, Random::random() * 2);
	dinosaurRenderPool->addRenderObject(drinkingDino1);
	_renderer.addAnimatedRenderObjectToShadowPool(drinkingDino1);
	_animatedObjects.push_back(drinkingDino1);

	rgl::AnimatedRenderObject* drinkingDino2 = new rgl::AnimatedRenderObject;
	drinkingDino2->setMesh(assets->getAnimatedMesh("anky"));
	drinkingDino2->setTexture(assets->getTexture("anky"));
	drinkingDino2->setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(82, 12.7f, 208.5f)) * glm::scale(glm::mat4(1), glm::vec3(1, 1, 1)) * glm::rotate(glm::mat4(1), -0.9f, glm::vec3(0, 1, 0))* glm::rotate(glm::mat4(1), 0.2f, glm::vec3(1, 0, 0)));
	//Randomly displace the animation
	drinkingDino2->setActiveAnimation(1, Random::random() * 2);
	dinosaurRenderPool->addRenderObject(drinkingDino2);
	_renderer.addAnimatedRenderObjectToShadowPool(drinkingDino2);
	_animatedObjects.push_back(drinkingDino2);

	//Idle dinos
	rgl::AnimatedRenderObject* idleDino1 = new rgl::AnimatedRenderObject;
	idleDino1->setMesh(assets->getAnimatedMesh("anky"));
	idleDino1->setTexture(assets->getTexture("anky"));
	idleDino1->setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(42, 18.5f, 262.0f)) * glm::scale(glm::mat4(1), glm::vec3(1, 1, 1)) * glm::rotate(glm::mat4(1), -2.4f, glm::vec3(0, 1, 0)));
	//Randomly displace the animation
	idleDino1->setActiveAnimation(0, Random::random() * 2);
	dinosaurRenderPool->addRenderObject(idleDino1);
	_renderer.addAnimatedRenderObjectToShadowPool(idleDino1);
	_animatedObjects.push_back(idleDino1);

	rgl::AnimatedRenderObject* idleDino2 = new rgl::AnimatedRenderObject;
	idleDino2->setMesh(assets->getAnimatedMesh("anky"));
	idleDino2->setTexture(assets->getTexture("anky"));
	idleDino2->setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(35, 18.5f, 255.0f)) * glm::scale(glm::mat4(1), glm::vec3(1, 1, 1)) * glm::rotate(glm::mat4(1), 0.4f, glm::vec3(0, 1, 0)));
	//Randomly displace the animation
	idleDino2->setActiveAnimation(0, Random::random() * 2);
	dinosaurRenderPool->addRenderObject(idleDino2);
	_renderer.addAnimatedRenderObjectToShadowPool(idleDino2);
	_animatedObjects.push_back(idleDino2);

	rgl::AnimatedRenderObject* idleDino3 = new rgl::AnimatedRenderObject;
	idleDino3->setMesh(assets->getAnimatedMesh("anky"));
	idleDino3->setTexture(assets->getTexture("anky"));
	idleDino3->setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(38, 18.5f, 265.0f)) * glm::scale(glm::mat4(1), glm::vec3(1, 1, 1)) * glm::rotate(glm::mat4(1), -3.0f, glm::vec3(0, 1, 0)));
	//Randomly displace the animation
	idleDino3->setActiveAnimation(0, Random::random() * 2);
	dinosaurRenderPool->addRenderObject(idleDino3);
	_renderer.addAnimatedRenderObjectToShadowPool(idleDino3);
	_animatedObjects.push_back(idleDino3);

	//Walking dinos
	for (int i = 0; i < NUMBER_OF_DINOS; ++i) {
		rgl::RenderObject* hat = new rgl::RenderObject;
		float randHat = Random::random() * 4;

		if (randHat < 1) {
			hat->setMesh(assets->getMesh("topHat"));
			hat->setTexture(assets->getTexture("topHat"));
			hatRenderPool->addRenderObject(hat);
			_renderer.addRenderObjectToShadowPool(hat);
		}
		else if (randHat < 2) {
			hat->setMesh(assets->getMesh("cowboyHat"));
			hat->setTexture(assets->getTexture("cowboyHat"));
			hatRenderPool->addRenderObject(hat);
			_renderer.addRenderObjectToShadowPool(hat);
		}
		else if (randHat < 3) {
			hat->setMesh(assets->getMesh("bowlerHat"));
			hat->setTexture(assets->getTexture("bowlerHat"));
			hatRenderPool->addRenderObject(hat);
			_renderer.addRenderObjectToShadowPool(hat);
		}



		rgl::AnimatedRenderObject* runningDino = new rgl::AnimatedRenderObject;
		runningDino->setMesh(assets->getAnimatedMesh("anky"));
		runningDino->setTexture(assets->getTexture("anky"));
		runningDino->setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(15 * i + Random::random() * 3 - 15, 0, 70 + 20*Random::random())) * glm::scale(glm::mat4(1), glm::vec3(1, 1, 1)) * glm::rotate(glm::mat4(1), -glm::half_pi<float>(), glm::vec3(0, 1, 0)));
		runningDino->getSkeleton()->getJoint(12)->attachRenderObject(hat,glm::translate(glm::mat4(1), glm::vec3(0,0.4f,0)) 
																				* glm::scale(glm::mat4(1),glm::vec3(0.3,0.3,0.3)) 
																				* glm::rotate(glm::mat4(1),0.7f, glm::vec3(1,0,0)));


		//Randomly displace the animation
		runningDino->setActiveAnimation(2, Random::random() * 2);
		_runningDinos.push_back(runningDino);
		_animatedObjects.push_back(runningDino);
		dinosaurRenderPool->addRenderObject(runningDino);
		_renderer.addAnimatedRenderObjectToShadowPool(runningDino);
	}

	//Setup post processing
	rgl::SkyboxFX* skybox = new rgl::SkyboxFX({assets->getShader("SkyboxVertexFX"), assets->getShader("SkyboxFragmentFX") },assets->getCubemap("valley"),_renderer.getDepthTexture(), _mainCamera);
	_renderer.addPostProcessingFX(skybox);

	_sceneNameText->setText("Dinosaur Valley");

}

void ValleyScene::draw(float delta)
{
	_cameraController->update(delta);

	if (_input.isKeyHeld(InputButton::KEYBOARD_T)) {
		int outerTes[3] = { 1,1,1 };
		_tesselationUniform->setTesselation(outerTes, 0);
	}
	else if (_input.isKeyHeld(InputButton::KEYBOARD_Y)) {
		int outerTes[3] = { 100,100,100 };
		_tesselationUniform->setTesselation(outerTes, 100);
	}
	else {
		int outerTes[3] = { 10,10,10 };
		_tesselationUniform->setTesselation(outerTes, 10);
	}



	_waterUniform->update(delta);

	updateDinos(delta);

	BaseScene::draw(delta);
}

void ValleyScene::updateDinos(float delta)
{
	for (auto& d : _runningDinos) {

		auto currentMatrix = d->getModelMatrix();

		if (currentMatrix[3].x < -25) {
			d->setModelMatrix(currentMatrix * glm::translate(glm::mat4(1), glm::vec3(0, 0, -200)));
		}
		else {
			d->setModelMatrix(currentMatrix * glm::translate(glm::mat4(1), glm::vec3(0, 0, DINO_SPEED*delta)));
		}


	}

	for (auto& ao : _animatedObjects) {
		ao->update(delta);
	}
}
