#pragma once

#include <RobGL/Renderer.h>
#include "AssetPack.h"
#include <Input/Input.h>

class BaseScene
{
public:
	BaseScene(Window& window, Input& input);
	~BaseScene();

	virtual void setupScene(AssetPack* assets) = 0;

	virtual void onResize(int width, int height);

	virtual void draw(float delta);

protected:
	rgl::Renderer _renderer;

	Input& _input;
};

