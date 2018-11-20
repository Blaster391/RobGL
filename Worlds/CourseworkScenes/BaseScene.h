#pragma once

#include <RobGL/Renderer.h>
#include "AssetPack.h"
#include <Input/Input.h>

#include <RobGL/AnimatedRenderObject.h>
#include <RobGL/UITextFX.h>

class BaseScene
{
public:
	BaseScene(Window& window, Input& input);
	~BaseScene();

	void setup(AssetPack* assets);

	virtual void onResize(int width, int height);

	virtual void draw(float delta);

protected:
	virtual void setupScene(AssetPack* assets) = 0;

	rgl::Renderer _renderer;

	Input& _input;

	int _frames = 0;
	float _seconds = 0;

	rgl::UITextFX* _fpsText;
	rgl::UITextFX* _sceneNameText;
};

