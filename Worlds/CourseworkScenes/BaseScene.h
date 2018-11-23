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
	virtual ~BaseScene();

	void setup(AssetPack* assets);

	void onResize(int width, int height);

	virtual void draw(float delta);



protected:
	bool drawUI = false;
	
	virtual void setupScene(AssetPack* assets) = 0;

	rgl::Renderer _renderer;

	Input& _input;

	int _frames = 0;
	float _seconds = 0;

	rgl::UITextFX* _fpsText;
	rgl::UITextFX* _sceneNameText;

	rgl::ScreenInformationUniform* _screenInfoUniform;

	rgl::PostProcessingFX* _renderNormals;
	rgl::PostProcessingFX* _renderRenderEmissive;
	rgl::PostProcessingFX* _renderDepth;
	rgl::PostProcessingFX* _depthOfFieldFX;

	rgl::Camera* _mainCamera;

};

