#pragma once
#include "BaseScene.h"
#include "CameraController.h"
class SpaceScene : public BaseScene
{
public:
	SpaceScene(Window& window, Input& input);
	virtual ~SpaceScene();

	virtual void setupScene(AssetPack* assets) override;
	virtual void draw(float delta) override;
private:
	CameraController* _cameraController;
};

