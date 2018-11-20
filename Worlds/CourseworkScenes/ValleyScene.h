#pragma once
#include "BaseScene.h"
#include "CameraController.h"



class ValleyScene : public BaseScene
{
public:
	ValleyScene(Window& window, Input& i);
	~ValleyScene();


	virtual void draw(float delta) override;
protected:
	virtual void setupScene(AssetPack* assets) override;

private:

	void updateDinos(float delta);

	CameraController* _cameraController;

	const int NUMBER_OF_DINOS = 10;
	const float DINO_SPEED = 10.0f;

	std::vector<rgl::AnimatedRenderObject*> _dinos;


};

