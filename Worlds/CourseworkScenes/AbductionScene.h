#pragma once
#include "BaseScene.h"
#include "CameraController.h"

#include <RobGL/ParticlePool.h>
#include <RobGL/ParticleSystem.h>
#include <RobGL_SceneGraph/SceneNode.h>


struct Abductee {
	rgl::RenderObject* RenderObject;
	float CurrentPosition = 0.0f;
	bool reverse = false;
	glm::vec3 originalPosition;
};

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

	std::vector<Abductee> _abductees;

	const float _dinoAbductSpeed = 1.0f;
	const float _dinoMovementRadius = 5.0f;
	const float _dinoMinScale = 0.1f;

	const int numberOfParticlesInBeam = 20000;
	rgl::Vertex* _beamParticles;
};

