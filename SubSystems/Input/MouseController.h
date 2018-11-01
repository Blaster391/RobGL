#pragma once
#include <Window/Window.h>
class MouseController
{
public:
	MouseController();
	~MouseController();

	void init(Window* w);
	void update();

	double getMousePositionX();
	double getMousePositionY();
	double getXDelta();
	double getYDelta();

private:
	Window* _window;

	double _mousePositionX;
	double _mousePositionY;

	double _previousPositionX;
	double _previousPositionY;
};

