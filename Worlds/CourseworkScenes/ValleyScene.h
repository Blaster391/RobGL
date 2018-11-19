#pragma once
#include "BaseScene.h"
#include "CameraController.h"

class ValleyScene : public BaseScene
{
public:
	ValleyScene(Window& window, Input& i);
	~ValleyScene();

	virtual void setupScene(AssetPack* assets) override;

	virtual void draw(float delta) override;
private:

	CameraController* _cameraController;
};

