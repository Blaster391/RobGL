#include "ValleyScene.h"


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
	directionalLightCamera->setProjectionOrthographic(100, 400, 300, 300);
	directionalLightCamera->setPosition(glm::vec3(200, 200, -20));
	directionalLightCamera->pitch(-0.6f);
	directionalLightCamera->yaw(-3.9f);
	rgl::ScreenInformationUniform*  screenInfoUniform = new rgl::ScreenInformationUniform(800, 600);

	_renderer.enableDeferredLighting({ assets->getShader("PointLightVertex"), assets->getShader("PointLightFragment") }, { assets->getShader("LightingCombineVertex"), assets->getShader("LightingCombineFragment") }, mainCamera, screenInfoUniform);
	_renderer.enableShadowMapping({assets->getShader("ShadowMapVertex"), assets->getShader("ShadowMapFragment")}, { assets->getShader("AnimatedShadowMapVertex"), assets->getShader("ShadowMapFragment") }, directionalLightCamera, 2160 * 4);

	directionalLightUniform->setShadowTexture(_renderer.getShadowMapTexture());

	//Setup render pools
	int outerTes[4] = { 10,10,10,10 };
	_tesselationUniform = new rgl::TesselationControlUniform(outerTes, 10);
	_tesselationLODUniform = new rgl::TesselationControlUniform(outerTes, 1);

	
	rgl::RenderPool* valleyRenderPoolLOD = new rgl::RenderPool({ assets->getShader("ValleyFloorVertex"), assets->getShader("ValleyFloorTessControl"), assets->getShader("ValleyFloorTessEvaluation"), assets->getShader("ValleyFloorFragment") }, mainCamera);
	rgl::AdditionalTextureUniform* textureUniform = new rgl::AdditionalTextureUniform(assets->getTexture("ground_sand"), "flatTex");
	valleyRenderPoolLOD->addUniformData(directionalLightUniform);
	valleyRenderPoolLOD->addUniformData(textureUniform);
	valleyRenderPoolLOD->addUniformData(_tesselationLODUniform);
	_renderer.addRenderPool(valleyRenderPoolLOD);

	rgl::RenderPool* valleyRenderPool = new rgl::RenderPool({ assets->getShader("ValleyFloorVertex"), assets->getShader("ValleyFloorTessControl"), assets->getShader("ValleyFloorTessEvaluation"), assets->getShader("ValleyFloorFragment") }, mainCamera);
	valleyRenderPool->addUniformData(directionalLightUniform);
	valleyRenderPool->addUniformData(textureUniform);
	valleyRenderPool->addUniformData(_tesselationUniform);
	_renderer.addRenderPool(valleyRenderPool);


	rgl::RenderPool* waterRenderPool = new rgl::RenderPool({ assets->getShader("ValleyFloorVertex"), assets->getShader("ValleyFloorTessControl"), assets->getShader("ValleyFloorTessEvaluation"), assets->getShader("ValleyFloorFragment") }, mainCamera);
	waterRenderPool->addUniformData(directionalLightUniform);
	waterRenderPool->addUniformData(_tesselationUniform);
	_renderer.addRenderPool(waterRenderPool);

	rgl::RenderPool* dinosaurRenderPool = new rgl::RenderPool({ assets->getShader("AnimatedVertex"), assets->getShader("TexturedFragment") }, mainCamera);
	dinosaurRenderPool->addUniformData(directionalLightUniform);
	_renderer.addRenderPool(dinosaurRenderPool);

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
	valleyRenderPoolLOD->addRenderObject(valleyFloor3);

	rgl::RenderObject* valleyFloor4 = new rgl::RenderObject;
	valleyFloor4->setMesh(assets->getMesh("valleyFloor_4"));
	valleyFloor4->setTexture(assets->getTexture("ground_rock"));
	valleyFloor4->setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(150, 0, 0)) * glm::scale(glm::mat4(1), glm::vec3(1, 5, 1)));
	valleyRenderPoolLOD->addRenderObject(valleyFloor4);

	rgl::RenderObject* water = new rgl::RenderObject;
	water->setMesh(assets->getMesh("flatMap"));
	water->setTexture(assets->getTexture("water"));
	water->setModelMatrix( glm::translate(glm::mat4(1), glm::vec3(15, 15, 185)) * glm::scale(glm::mat4(1), glm::vec3(0.7, 1, 0.7)));
	waterRenderPool->addRenderObject(water);

	//Setup dinosaurs
	for (int i = 0; i < NUMBER_OF_DINOS; ++i) {
		rgl::AnimatedRenderObject* dino = new rgl::AnimatedRenderObject;
		dino->setMesh(assets->getAnimatedMesh("anky"));
		dino->setTexture(assets->getTexture("anky"));
		dino->setModelMatrix(glm::translate(glm::mat4(1), glm::vec3(15 * i + Random::random() * 3, -3.5, i + 70 + 10*Random::random())) * glm::scale(glm::mat4(1), glm::vec3(1, 1, 1)) * glm::rotate(glm::mat4(1), -glm::half_pi<float>(), glm::vec3(0, 1, 0)));
		
		//Randomly displace the animation
		dino->setActiveAnimation(0, Random::random() * 2);
		_dinos.push_back(dino);
		dinosaurRenderPool->addRenderObject(dino);
		_renderer.addAnimatedRenderObjectToShadowPool(dino);
	}

	//Setup post processing
	rgl::SkyboxFX* skybox = new rgl::SkyboxFX({assets->getShader("SkyboxVertexFX"), assets->getShader("SkyboxFragmentFX") },assets->getCubemap("valley"),_renderer.getDepthTexture(), mainCamera);
	_renderer.addPostProcessingFX(skybox);

	_sceneNameText->setText("Dinosaur Valley");

}

void ValleyScene::draw(float delta)
{
	_cameraController->update(delta);

	if (_input.isKeyPressed(InputButton::KEYBOARD_T)) {
		int outerTes[4] = { 1,1,1,1 };
		_tesselationUniform->setTesselation(outerTes, 1);
		_tesselationLODUniform->setTesselation(outerTes, 1);
	}

	updateDinos(delta);

	BaseScene::draw(delta);
}

void ValleyScene::updateDinos(float delta)
{
	for (auto& d : _dinos) {

		auto currentMatrix = d->getModelMatrix();

		if (currentMatrix[3].x < -25) {
			d->setModelMatrix(currentMatrix * glm::translate(glm::mat4(1), glm::vec3(0, 0, -200)));
		}
		else {
			d->setModelMatrix(currentMatrix * glm::translate(glm::mat4(1), glm::vec3(0, 0, DINO_SPEED*delta)));
		}
	}
}
