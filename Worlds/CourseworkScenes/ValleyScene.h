#pragma once
#include "BaseScene.h"
#include "CameraController.h"
#include <RobGL/AnimatedRenderObject.h>
#include <RobGL/UITextFX.h>


class ValleyScene : public BaseScene
{
public:
	ValleyScene(Window& window, Input& i);
	~ValleyScene();

	virtual void setupScene(AssetPack* assets) override;

	virtual void draw(float delta) override;
private:

	CameraController* _cameraController;

	const int NUMBER_OF_DINOS = 10;

	std::vector<rgl::AnimatedRenderObject*> _dinos;

	int _frames = 0;
	float _seconds = 0;

	rgl::UITextFX* _fpsText;
	rgl::UITextFX* _sceneNameText;
};

