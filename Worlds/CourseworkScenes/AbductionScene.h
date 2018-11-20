#pragma once
#include "BaseScene.h"
#include "CameraController.h"

#include <RobGL/ParticlePool.h>
#include <RobGL/ParticleSystem.h>
#include <RobGL_SceneGraph/SceneNode.h>


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
	rgl::ScreenInformationUniform*  _screenInfoUniform;

	rgl::scenes::SceneNode* _ufoNode;
	const float _ufoRotateSpeed = 1.0f;
	float _currentUfoRotation = 0;
};

