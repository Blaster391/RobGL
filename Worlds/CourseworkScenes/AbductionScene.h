#pragma once
#include "BaseScene.h"
#include "CameraController.h"
class AbductionScene :
	public BaseScene
{
public:
	AbductionScene(Window& window, Input& input);
	~AbductionScene();

	virtual void draw(float delta) override;
protected:
	virtual void setupScene(AssetPack* assets) override;
private:
	CameraController* _cameraController;
};

