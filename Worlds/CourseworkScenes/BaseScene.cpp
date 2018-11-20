#include "BaseScene.h"
#include <RobGL/AdditionalTextureUniform.h>

BaseScene::BaseScene(Window& window, Input& input) : _renderer(window), _input(input)
{
}

BaseScene::~BaseScene()
{
}

void BaseScene::setup(AssetPack * assets)
{

	_fpsText = new rgl::UITextFX({ assets->getShader("TextVertex"), assets->getShader("TextFragment") }, assets->getText());
	_fpsText->setColour(glm::vec4(1, 1, 1, 1));
	_fpsText->setPosition(0.5f, 0.75f);
	_fpsText->setScale(0.1f);
	_fpsText->setText("FPS: 1234");

	_sceneNameText = new rgl::UITextFX({ assets->getShader("TextVertex"), assets->getShader("TextFragment") }, assets->getText());
	_sceneNameText->setColour(glm::vec4(1, 1, 1, 1));
	_sceneNameText->setPosition(0.25f, -0.5f);
	_sceneNameText->setScale(0.1f);

	_renderNormals = new rgl::PostProcessingFX({ assets->getShader("TexturedVertex_NO_MVP"), assets->getShader("RenderFBOFragmentFX") }, 1);
	_renderRenderEmissive = new rgl::PostProcessingFX({ assets->getShader("TexturedVertex_NO_MVP"), assets->getShader("RenderFBOFragmentFX") }, 1);
	_renderDepth = new rgl::PostProcessingFX({ assets->getShader("TexturedVertex_NO_MVP"), assets->getShader("RenderDepthFBOFragmentFX") }, 1);


	//Actually setup the scene
	setupScene(assets);

	_renderNormals->addUniformData(new rgl::AdditionalTextureUniform(_renderer.getNormalsTexture(), "overrideTex"));
	_renderRenderEmissive->addUniformData(new rgl::AdditionalTextureUniform(_renderer.getEmissiveTexture(), "overrideTex"));
	_renderDepth->addUniformData(new rgl::AdditionalTextureUniform(_renderer.getDepthTexture(), "overrideTex"));

	_renderer.addPostProcessingFX(_renderNormals);
	_renderer.addPostProcessingFX(_renderRenderEmissive);
	_renderer.addPostProcessingFX(_renderDepth);

	_renderer.addPostProcessingFX(_fpsText);
	_renderer.addPostProcessingFX(_sceneNameText);
}

void BaseScene::onResize(int width, int height)
{
	_renderer.resize(width, height);
}

void BaseScene::draw(float delta)
{
	//Update framerate
	_seconds += delta;
	_frames++;
	if (_seconds > 1) {
		_seconds = 0;

		_fpsText->setText("FPS: " + std::to_string(_frames));
		_frames = 0;
	}

	if (_input.isKeyHeld(InputButton::KEYBOARD_1)) {
		_renderNormals->setEnabled(true);
		_renderRenderEmissive->setEnabled(false);
		_renderDepth->setEnabled(false);
	}
	else if (_input.isKeyHeld(InputButton::KEYBOARD_2)) {
		_renderNormals->setEnabled(false);
		_renderRenderEmissive->setEnabled(true);
		_renderDepth->setEnabled(false);
	}
	else if (_input.isKeyHeld(InputButton::KEYBOARD_3)) {
		_renderNormals->setEnabled(false);
		_renderRenderEmissive->setEnabled(false);
		_renderDepth->setEnabled(true);
	}
	else {
		_renderNormals->setEnabled(false);
		_renderRenderEmissive->setEnabled(false);
		_renderDepth->setEnabled(false);
	}


	_renderer.update(delta);
}
