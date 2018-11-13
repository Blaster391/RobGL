#include "CameraController.h"


CameraController::CameraController(rgl::Camera * c, Input * i) : _camera(c), _input(i)
{
}

CameraController::~CameraController()
{
}

void CameraController::update(float delta)
{
	auto pos = glm::inverse(_camera->getViewMatrix());
	
	delta = delta * 20;

	if (_input->isKeyPressed(InputButton::KEYBOARD_Q)) {
		_camera->setProjectionOrthographic();
	}
	if (_input->isKeyPressed(InputButton::KEYBOARD_R)) {
		_camera->setProjectionPerspective();
	}		
	if (_input->isKeyHeld(InputButton::KEYBOARD_W)) {
		_camera->translate(-glm::normalize(pos[2]) * delta);
	}
	else if (_input->isKeyHeld(InputButton::KEYBOARD_S)) {
		_camera->translate(glm::normalize(pos[2]) * delta);
	}

	if (_input->isKeyHeld(InputButton::KEYBOARD_A)) {
		_camera->translate(-glm::normalize(pos[0]) * delta);
	}
	else if (_input->isKeyHeld(InputButton::KEYBOARD_D)) {
		_camera->translate(glm::normalize(pos[0]) * delta);
	}

	if (_input->isKeyHeld(InputButton::KEYBOARD_Z)) {
		_camera->translate(glm::normalize(pos[1]) * delta);
	}
	else if (_input->isKeyHeld(InputButton::KEYBOARD_X)) {
		_camera->translate(-glm::normalize(pos[1]) * delta);
	}

	//TODO sensitivity
	_camera->pitch(-_input->Mouse().getYDelta() * 0.001f);
	_camera->yaw(-_input->Mouse().getXDelta() * 0.001f);
}

rgl::Camera * CameraController::getCamera()
{
	return _camera;
}
