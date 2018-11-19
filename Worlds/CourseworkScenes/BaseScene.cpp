#include "BaseScene.h"

BaseScene::BaseScene(Window& window, Input& input) : _renderer(window), _input(input)
{
}

BaseScene::~BaseScene()
{
}

void BaseScene::onResize(int width, int height)
{
	_renderer.resize(width, height);
}

void BaseScene::draw(float delta)
{
	_renderer.update(delta);
}
