#pragma once
#include "BaseScene.h"
class SpaceScene : public BaseScene
{
public:
	SpaceScene(Window& window);
	virtual ~SpaceScene();

	virtual void setupScene(AssetPack* assets) override;
};

