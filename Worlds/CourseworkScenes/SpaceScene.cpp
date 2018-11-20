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




	rgl::SkyboxFX* skybox = new rgl::SkyboxFX({ assets->getShader("SkyboxVertexFX"), assets->getShader("SkyboxFragmentFX") }, assets->getCubemap("space_red"), _renderer.getDepthTexture(), mainCamera);

	_renderer.addPostProcessingFX(skybox);

	_sceneNameText->setText("Spaaaacccceee");
}

void SpaceScene::draw(float delta)
{
	_cameraController->update(delta);
	BaseScene::draw(delta);
}
