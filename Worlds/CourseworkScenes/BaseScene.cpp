#include "BaseScene.h"

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

	//Actually setup the scene
	setupScene(assets);


	//_sceneNameText->setText("Dinosaur Valley");


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

	_renderer.update(delta);
}
