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
	bool _lockToEarth = true;


	CameraController* _cameraController;
	rgl::Camera* _mainCamera;
	LerpSkyboxUniform* _skyboxUniform;

	rgl::scenes::SceneNode* _sunNode;

	rgl::scenes::SceneNode* _earthNode;
	rgl::scenes::SceneNode* _earthAtmosphereNode;
	rgl::scenes::SceneNode* _moonNode;
	rgl::scenes::SceneNode* _moonMoonNode;
	rgl::scenes::SceneNode* _ufoNode;

	rgl::scenes::SceneNode* _jupiterNode;
	rgl::scenes::SceneNode* _jupiterMoonNode;
	rgl::scenes::SceneNode* _mercuryNode;
	rgl::scenes::SceneNode* _saturnNode;


	float _earthAtmosphereRotateAmount = 0.0f;
	const float _earthAtmosphereRotateSpeed = 0.1f;

	float _currentMoonOrbit = 2.3f;
	const float _moonOrbitRadius = 8.0f;
	const float _moonOrbitSpeed = -0.75f;

	float _currentMercuryOrbit = 1.1f;
	const float _mercuryOrbitRadius = 5.0f;
	const float _mercuryOrbitSpeed = 1.0f;

	float _currentSaturnOrbit = 3.0f;
	const float _saturnOrbitRadius = 50.0f;
	const float _saturnOrbitSpeed = 0.3f;

	float _currentJupiterOrbit = 0.4f;
	const float _jupiterOrbitRadius = 35.0f;
	const float _jupiterOrbitSpeed = -0.1f;

	float _currentJupiterMoonOrbit = 7.4f;
	const float _jupiterMoonOrbitRadius = 10.0f;
	const float _jupiterMoonOrbitSpeed = 0.1f;

	float _currentEarthOrbit = 0.0f;
	const float _earthOrbitRadius = 10.0f;
	const float _earthOrbitSpeed = 0.25f;


	//Helper method since many things orbit
	glm::vec3 calculateOrbit(float pos, float radius) {
		return glm::vec3(sin(pos), 0, cos(pos)) * radius;
	}
};

