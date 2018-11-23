#pragma once
#include "BaseScene.h"
#include "CameraController.h"

#include <RobGL/SkyboxFX.h>
#include <RobGL/DirectionalLightCamera.h>
#include <RobGL/AdditionalTextureUniform.h>
#include <RobGL/TesselationControlUniform.h>
#include <RobGL/WaterUniform.h>

class ValleyScene : public BaseScene
{
public:
	ValleyScene(Window& window, Input& i);
	virtual ~ValleyScene();


	virtual void draw(float delta) override;
protected:
	virtual void setupScene(AssetPack* assets) override;

private:

	void updateDinos(float delta);

	CameraController* _cameraController;

	const int NUMBER_OF_DINOS = 15;
	const float DINO_SPEED = 10.0f;

	std::vector<rgl::AnimatedRenderObject*> _runningDinos;
	std::vector<rgl::AnimatedRenderObject*> _animatedObjects;

	rgl::TesselationControlUniform* _tesselationUniform;
	rgl::WaterUniform* _waterUniform;
};

