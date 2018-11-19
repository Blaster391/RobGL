#include "ValleyScene.h"

#include <RobGL/SkyboxFX.h>

ValleyScene::ValleyScene(Window& window, Input& i) : BaseScene(window, i)
{
}

ValleyScene::~ValleyScene()
{
}

void ValleyScene::setupScene(AssetPack * assets)
{
	rgl::Camera* mainCamera = new rgl::Camera;
	_cameraController = new CameraController(mainCamera, &_input);

	_renderer.enablePostProcessing({ assets->getShader("TexturedVertex"), assets->getShader("UnlitTexturedFragment") });

	mainCamera->setProjectionOrthographic();




	rgl::SkyboxFX* skybox = new rgl::SkyboxFX({assets->getShader("SkyboxVertexFX"), assets->getShader("SkyboxFragmentFX") },assets->getCubemap("valley"),_renderer.getDepthTexture(), mainCamera);

	_renderer.addPostProcessingFX(skybox);


}

void ValleyScene::draw(float delta)
{
	_cameraController->update(delta);
	BaseScene::draw(delta);
}
