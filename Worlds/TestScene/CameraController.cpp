#include "CameraController.h"


CameraController::CameraController(rgl::Camera * c, Input * i) : _camera(c), _input(i)
{
}

CameraController::~CameraController()
{
}

void CameraController::update(float delta)
{
	if (_input->isKeyPressed(InputButton::KEYBOARD_Q)) {
		_camera->setProjectionOrthographic();
	}
	if (_input->isKeyPressed(InputButton::KEYBOARD_R)) {
		_camera->setProjectionPerspective();
	}		
	if (_input->isKeyHeld(InputButton::KEYBOARD_W)) {
		_camera->translate(-glm::vec3(0, 0, 0.1f));
	}
	else if (_input->isKeyHeld(InputButton::KEYBOARD_S)) {
		_camera->translate(glm::vec3(0, 0, 0.1f));
	}

	if (_input->isKeyHeld(InputButton::KEYBOARD_A)) {
		_camera->translate(-glm::vec3(0.1f, 0, 0));
	}
	else if (_input->isKeyHeld(InputButton::KEYBOARD_D)) {
		_camera->translate(glm::vec3(0.1f, 0, 0));
	}

	if (_input->isKeyHeld(InputButton::KEYBOARD_Z)) {
		_camera->translate(glm::vec3(0, 0.1f, 0));
	}
	else if (_input->isKeyHeld(InputButton::KEYBOARD_X)) {
		_camera->translate(-glm::vec3(0, 0.1f, 0));
	}

	//TODO sensitivity
	_camera->pitch(-_input->Mouse().getYDelta() * 0.001f);
	_camera->yaw(-_input->Mouse().getXDelta() * 0.001f);
}

rgl::Camera * CameraController::getCamera()
{
	return _camera;
}
