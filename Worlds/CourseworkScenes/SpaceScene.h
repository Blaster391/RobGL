#pragma once
#include "BaseScene.h"
#include "CameraController.h"
#include "LerpSkyboxUniform.h"
#include <RobGL_SceneGraph/SceneNode.h>


class SpaceScene : public BaseScene
{
public:
	SpaceScene(Window& window, Input& input);
	virtual ~SpaceScene();


	virtual void draw(float delta) override;
protected:
	virtual void setupScene(AssetPack* assets) override;
private:
	CameraController* _cameraController;
	LerpSkyboxUniform* _skyboxUniform;

	rgl::scenes::SceneNode* _sunNode;

	rgl::scenes::SceneNode* _earthNode;
	rgl::scenes::SceneNode* _earthAtmosphereNode;
	rgl::scenes::SceneNode* _moonNode;

	float _earthAtmosphereRotateAmount = 0.0f;
	const float _earthAtmosphereRotateSpeed = 0.1f;
	const float _moonOrbitRadius = 8.0f;
	float _currentMoonOrbit = 0.0f;
	const float _moonOrbitSpeed = -0.75f;

	float _currentEarthOrbit = 0.0f;
	const float _earthOrbitSpeed = 0.25f;
	const float _earthOrbitRadius = 50.0f;

	//Helper method since many things orbit
	glm::vec3 calculateOrbit(float pos, float radius) {
		return glm::vec3(sin(pos), 0, cos(pos)) * radius;
	}
};

