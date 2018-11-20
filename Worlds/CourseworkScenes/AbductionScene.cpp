#include "AbductionScene.h"




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

	_renderer.enablePostProcessing({ assets->getShader("TexturedVertex"), assets->getShader("UnlitTexturedFragment") });

	mainCamera->setProjectionPerspective(800, 600);


	_sceneNameText->setText("Alien Abduction");
}


void AbductionScene::draw(float delta)
{


	BaseScene::draw(delta);
}


