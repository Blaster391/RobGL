#include "MouseController.h"



MouseController::MouseController()
{
}


MouseController::~MouseController()
{
}

void MouseController::init(Window * w)
{
	_window = w;

	auto positions = _window->getCursorPosition();

	_mousePositionX = positions.first;
	_mousePositionY = positions.second;

	_previousPositionX = _mousePositionX;
	_previousPositionY = _mousePositionY;
}

void MouseController::update()
{
	_previousPositionX = _mousePositionX;
	_previousPositionY = _mousePositionY;

	auto positions = _window->getCursorPosition();

	_mousePositionX = positions.first;
	_mousePositionY = positions.second;
}

double MouseController::getMousePositionX()
{
	return _mousePositionX;
}

double MouseController::getMousePositionY()
{
	return _mousePositionY;
}

double MouseController::getXDelta()
{
	return _mousePositionX - _previousPositionX;
}

double MouseController::getYDelta()
{
	return _mousePositionY - _previousPositionY;
}
