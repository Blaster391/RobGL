#include "BaseScene.h"



BaseScene::BaseScene()
{
}


BaseScene::~BaseScene()
{
}

void BaseScene::onResize(int width, int height)
{
}

void BaseScene::draw(float delta)
{
	_renderer.update(delta);
}
