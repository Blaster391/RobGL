#pragma once
#include <RobGL/Camera.h>
#include <Input/Input.h>
class CameraController
{
public:
	CameraController(rgl::Camera* c, Input* i);
	~CameraController();

	void update();

	rgl::Camera* getCamera();
	
private:
	rgl::Camera* _camera;
	Input* _input;
};

